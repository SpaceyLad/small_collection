#!/bin/bash

journalctl --vacuum-time=7d
apt-get autoclean -y
apt-get update -y
apt-get dist-upgrade -y
apt-get upgrade -y
apt-get auto-remove -y
apt-get clean -y

echo "System is updated :]"
