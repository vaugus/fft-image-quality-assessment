#!/bin/sh

googletest=./googletest
googletestURL=https://github.com/google/googletest/archive/refs/heads/main.zip

if [ ! -d "$googletest" ]; then
  downloadsDir="$(mktemp -d)"
  wget $googletestURL -O "$downloadsDir"/main.zip
  unzip -q "$downloadsDir"/main.zip
  rm -f main.zip
  mv googletest-main googletest
fi

googletestHeaders=$(find $googletest/googletest/include -type f -name '*.h')
export googletestSources="$googletest/googletest/src/* $googletestHeaders"
