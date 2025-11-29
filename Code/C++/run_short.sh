#!/usr/bin/env bash
exe="${1%.*}"          # strip .cpp / .exe if given (e.g. g, g.cpp, g.exe)
for f in "$exe"*.in; do
  [ -e "$f" ] || continue
  echo "=== $f ==="
  "./$exe" < "$f"
done