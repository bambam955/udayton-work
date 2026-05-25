#!/usr/bin/env bash

set -eu

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(git -C "$SCRIPT_DIR" rev-parse --show-toplevel)"

sudo -v

# Install necessary packages
echo "Installing packages..."
for pkg in php libapache2-mod-php mysql-server php-mysqli; do
	apt show $pkg >/dev/null 2>&1 || sudo apt-get install -y $pkg
done

# Install SSL keys
echo "Installing SSL keys..."
sudo cp -t /etc/ssl "$REPO_ROOT"/conf/certs/*

# Install Apache site configurations
echo "Installing Apache site config..."
sudo cp -t /etc/apache2/sites-available "$REPO_ROOT"/conf/sites/*

# Update and restart the Apache web server
echo "Installing Apache modules..."
sudo a2enmod ssl >/dev/null
echo "Enabling websites..."
sudo a2ensite default-ssl.conf >/dev/null
sudo a2ensite secad-team-project-ssl.conf >/dev/null
grep 'minifacebook.io' /etc/hosts || echo -e '127.0.0.1\tsecad-team2.minifacebook.io' | sudo tee --append /etc/hosts

echo "Restarting Apache server..."
sudo systemctl daemon-reload && sudo systemctl restart apache2

echo "SUCCESS."
