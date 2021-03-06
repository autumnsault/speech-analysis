#!/bin/bash

unset `env | \
    grep -vi '^EDITOR=\|^HOME=\|^LANG=\|MXE\|^PATH=\|^BUILD_WINDOWS=\|^EXE_WINDOWS=' | \
    grep -vi 'PKG_CONFIG\|PROXY\|^PS1=\|^TERM=' | \
    cut -d '=' -f1 | tr '\n' ' '`
export PATH=$MXE/usr/bin:$PATH

export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'

export CROSS=i686-w64-mingw32.shared-

mkdir -p cmake-build-release-win
cd cmake-build-release-win

${CROSS}cmake -DCMAKE_BUILD_TYPE=Release ..
make 

$MXE/tools/copydlldeps.sh \
    --infile $EXE_WINDOWS \
    --destdir $BUILD_WINDOWS \
    --recursivesrcdir cmake-build-release-win/libtorch \
    --recursivesrcdir $MXE/usr/${CROSS::-1}/ \
    --loglevel 0 --copy --objdump $MXE/usr/bin/${CROSS}objdump >copydlls.log 2>&1
