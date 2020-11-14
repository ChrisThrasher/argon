#!/bin/bash

clang-format -i `find src -name *.cpp` `find include -name *.h`
