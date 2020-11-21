#!/bin/bash

clang-format -i `find include -name *.h` test/Example.cpp
