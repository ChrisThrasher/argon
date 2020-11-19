#!/bin/bash

clang-tidy test/Example.cpp include/Options/*.h -p build/compile_commands.json
