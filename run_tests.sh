#!/usr/bin/env bash

search_dir=$(find build -name *_test)
readarray -t test_files <<<"$search_dir"
for entry in ${test_files[@]}
do
  "$entry"
done
