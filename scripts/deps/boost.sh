#!/usr/bin/env bash
git clone git@github.com:boostorg/boost.git
cd boost
git checkout boost-1.65.1
git submodule update --init tools/boostdep tools/build
git submodule update --init libs/test
python tools/boostdep/depinst/depinst.py test
./bootstrap.sh gcc
./b2 -j4 --with-test --build-type=minimal variant=release --toolset=gcc address-model=64 stage --layout=system