#!/bin/bash

clang-tidy `find src -name *.cpp` `find include -name *.h` test/Example.cpp -p build/compile_commands.json
