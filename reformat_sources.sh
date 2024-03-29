#!/bin/sh

find . \( -iname *.h -o -iname *.cpp \) -a -not -path "./lib/3rdparty/*" | xargs clang-format -i
