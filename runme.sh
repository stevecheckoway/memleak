#!/bin/sh

set -e

echo '\033[1;32mCompiling\033[0m'
ruby extconf.rb
make

echo
echo '\033[1;32mRunning without limits\033[0m'
ruby crash.rb

echo
echo '\033[1;32mRunning with limits\033[0m'
ulimit -v 102400
ruby crash.rb
