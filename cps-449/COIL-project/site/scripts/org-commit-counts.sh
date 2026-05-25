#!/usr/bin/env bash

set -euo pipefail

# Resolve paths once so the script can be run from anywhere in the repo.
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

ORG="UD-CPS449-COILPROJECT"
FORMAT="markdown"
IDENTITY_FILE="$SCRIPT_DIR/commit-identities.psv"
SHORTLOG_ARGS="-sn --all --no-merges"

usage() {
  cat <<'EOF'
Usage: scripts/org-commit-counts.sh [options]

Generate per-team-member commit totals across every non-fork, non-archived
repository in a GitHub organization by cloning each repo as a temporary mirror
and aggregating `git shortlog` output.

Options:
  --org ORG_NAME                 GitHub organization to scan.
  --identity-file PATH           Pipe-delimited mapping file for author aliases.
  --shortlog-args "ARGS"         Quoted git shortlog arguments to use.
  --format markdown|tsv          Output format. Default: markdown.
  --help                         Show this help text.

Examples:
  scripts/org-commit-counts.sh
  scripts/org-commit-counts.sh --shortlog-args "-sn --all"
  scripts/org-commit-counts.sh --format tsv
EOF
}

require_command() {
  if ! command -v "$1" >/dev/null 2>&1; then
    echo "Missing required command: $1" >&2
    exit 1
  fi
}

normalize_key() {
  printf '%s' "$1" | tr '[:upper:]' '[:lower:]'
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --org)
      ORG="$2"
      shift 2
      ;;
    --identity-file)
      IDENTITY_FILE="$2"
      shift 2
      ;;
    --shortlog-args)
      SHORTLOG_ARGS="$2"
      shift 2
      ;;
    --format)
      FORMAT="$2"
      shift 2
      ;;
    --help|-h)
      usage
      exit 0
      ;;
    *)
      echo "Unknown option: $1" >&2
      usage >&2
      exit 1
      ;;
  esac
done

if [[ ! -f "$IDENTITY_FILE" ]]; then
  echo "Identity file not found: $IDENTITY_FILE" >&2
  exit 1
fi

case "$FORMAT" in
  markdown|tsv)
    ;;
  *)
    echo "Unsupported format: $FORMAT" >&2
    exit 1
    ;;
esac

require_command gh
require_command git
require_command sort

declare -A AUTHOR_TO_CANONICAL=()
declare -A USERNAME_BY_CANONICAL=()
declare -A CANONICAL_MEMBERS=()
declare -A TOTALS=()

# The identity file is the single place where alias cleanup happens, which keeps
# the aggregation logic simple and makes unmapped authors obvious.
while IFS='|' read -r canonical username alias; do
  [[ -z "${canonical:-}" ]] && continue
  [[ "$canonical" == \#* ]] && continue

  CANONICAL_MEMBERS["$canonical"]=1
  USERNAME_BY_CANONICAL["$canonical"]="$username"
  TOTALS["$canonical"]=0

  if [[ -n "${alias:-}" ]]; then
    AUTHOR_TO_CANONICAL["$(normalize_key "$alias")"]="$canonical"
  fi
done < "$IDENTITY_FILE"

workdir=$(mktemp -d "${TMPDIR:-/tmp}/org-commit-counts.XXXXXX")
trap 'rm -rf "$workdir"' EXIT

shortlog_extra=()
read -r -a shortlog_extra <<< "$SHORTLOG_ARGS"

repos_output=$(gh api "orgs/$ORG/repos?per_page=100" --paginate --jq '.[] | select(.fork | not) | select(.archived | not) | .full_name')

if [[ -z "$repos_output" ]]; then
  echo "No repositories found for organization: $ORG" >&2
  exit 1
fi

unmapped_file="$workdir/unmapped.tsv"
touch "$unmapped_file"

while IFS= read -r repo; do
  [[ -z "$repo" ]] && continue

  repo_name=${repo##*/}
  mirror_dir="$workdir/$repo_name.git"

  # `gh repo clone` uses the user's authenticated GitHub CLI setup, so it works
  # for private org repos without requiring manual SSH or HTTPS configuration.
  gh repo clone "$repo" "$mirror_dir" -- --mirror >/dev/null 2>&1

  while IFS=$'\t' read -r raw_count raw_author; do
    [[ -z "${raw_count:-}" ]] && continue

    count=$(printf '%s' "$raw_count" | tr -d '[:space:]')
    author_key=$(normalize_key "$raw_author")
    canonical=${AUTHOR_TO_CANONICAL["$author_key"]:-}

    if [[ -z "$canonical" ]]; then
      printf '%s\t%s\t%s\n' "$repo" "$count" "$raw_author" >> "$unmapped_file"
      continue
    fi

    TOTALS["$canonical"]=$(( TOTALS["$canonical"] + count ))
  done < <(git -C "$mirror_dir" shortlog "${shortlog_extra[@]}" -s -e)
done <<< "$repos_output"

if [[ -s "$unmapped_file" ]]; then
  echo "Unmapped authors found. Update $IDENTITY_FILE before using this output:" >&2
  sort -u "$unmapped_file" >&2
  exit 1
fi

rows_file="$workdir/rows.tsv"
for canonical in "${!CANONICAL_MEMBERS[@]}"; do
  printf '%s\t%s\t%s\n' "${TOTALS[$canonical]:-0}" "$canonical" "${USERNAME_BY_CANONICAL[$canonical]:-}" >> "$rows_file"
done

sorted_rows=$(sort -t $'\t' -k1,1nr -k2,2 "$rows_file")

case "$FORMAT" in
  markdown)
    echo "| Team Member | Commits |"
    echo "| --- | ---: |"
    while IFS=$'\t' read -r count canonical username; do
      [[ -z "${canonical:-}" ]] && continue

      # Keep the contributor name clickable in the generated Markdown so the
      # stats table can live directly in CONTRIBUTORS.md without a separate
      # GitHub column.
      member_display="$canonical"
      if [[ -n "${username:-}" ]]; then
        member_display="[$canonical](https://github.com/$username)"
      fi
      printf '| %s | %s |\n' "$member_display" "$count"
    done <<< "$sorted_rows"
    ;;
  tsv)
    echo -e "team_member\tgithub\tcommits"
    while IFS=$'\t' read -r count canonical username; do
      [[ -z "${canonical:-}" ]] && continue
      printf '%s\t%s\t%s\n' "$canonical" "$username" "$count"
    done <<< "$sorted_rows"
    ;;
esac
