#!/bin/bash

clang-tidy `find include -name *.h` test/Example.cpp -p build/compile_commands.json
