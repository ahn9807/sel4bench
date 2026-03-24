#!/bin/bash
#

mkdir -p build/
pushd build/
../init-build.sh -DPLATFORM=x86_64 -DRELEASE=TRUE -DFAULT=TRUE -DFASTPATH=TRUE -DKernelSkimWindow=TRUE
# ../init-build.sh -DPLATFORM=x86_64 -DRELEASE=FALSE -DFAULT=TRUE -DFASTPATH=TRUE -DKernelSkimWindow=TRUE -DKernelDebugBuild=ON -DKernelPrinting=ON
ninja
popd
