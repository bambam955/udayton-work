#!/usr/bin/env bash

set -eu

echo "Setting up DB..."

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

sudo mysql < "$SCRIPT_DIR/init.sql"

echo "SUCCESS."
