#!/usr/bin/env bash

set -eu

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(git -C "$SCRIPT_DIR" rev-parse --show-toplevel)"

sudo -v

DEPLOY_DIR=/var/www/html/minifacebook

sudo mkdir -p "$DEPLOY_DIR/public" "$DEPLOY_DIR/src"
(cd "$REPO_ROOT/public" && sudo cp -r . "$DEPLOY_DIR/public")
(cd "$REPO_ROOT/src" && sudo cp -r . "$DEPLOY_DIR/src")
