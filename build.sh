#!/bin/bash
#

mkdir -p build/
pushd build/
../init-build.sh -DPLATFORM=x86_64 -DRELEASE=TRUE -DFAULT=TRUE -DFASTPATH=TRUE
ninja
popd
