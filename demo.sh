#!/usr/bin/env bash
# runs through the demo for my presentation, press enter to go to the next step
set -u
cd "$(dirname "$0")"

# compile everything first
for f in 01_admin_flag 02_stack_smash 03_aslr 04_fixed; do
    gcc "$f.c" -o "$f" || exit 1
done

step() { echo; echo "----------------------------------------"; echo "\$ $*"; read -r -p "[enter]" _; "$@"; }

echo "1) Normal input"
step ./01_admin_flag alice

echo; echo "2) 16 chars of padding + 1 extra byte spills into is_admin"
step ./01_admin_flag AAAAAAAAAAAAAAAAB

echo; echo "3) Same input, with the bounded copy"
step ./04_fixed AAAAAAAAAAAAAAAAB

LONG=$(printf 'A%.0s' {1..64})
echo; echo "4) 64 bytes into a 16-byte buffer - the stack canary catches it"
step ./02_stack_smash "$LONG"

echo; echo "5) ASLR - addresses change every run"
step bash -c './03_aslr; echo; ./03_aslr'
