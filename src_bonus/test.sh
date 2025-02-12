#!/bin/bash
for file in *.c; do
    base="${file%.c}"
    mv "$file" "${base}_bonus.c"
done
echo "Cファイルのリネーム完了"

