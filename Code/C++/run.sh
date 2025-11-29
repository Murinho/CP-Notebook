#!/usr/bin/env bash
exe="${1%.*}"

# auto compile if .cpp exists
[ -f "$exe.cpp" ] && g++ -O2 -std=gnu++17 "$exe.cpp" -o "$exe"

for f in "$exe"*.in; do
  [ -e "$f" ] || continue
  echo -e "\033[1;34m=== $f ===\033[0m"

  start=$(date +%s%3N)
  "./$exe" < "$f"
  status=$?
  end=$(date +%s%3N)

  echo "Time: $((end - start)) ms"

  if [ $status -ne 0 ]; then
    echo "Runtime error"
    break
  fi

  if [ -f "${f%.in}.out" ]; then
    if diff -q <("./$exe" < "$f") "${f%.in}.out" >/dev/null; then
      echo "OK"
    else
      echo "WA"
    fi
  fi

  echo
done

# Make it executable with: chmod +x run.sh
# Run the testcases with: ./run.sh a.exe