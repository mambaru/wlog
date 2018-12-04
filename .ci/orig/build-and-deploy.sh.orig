#!/bin/bash
prjname=$1
refname=$2
buildtype=$3
shared_static=$4
shared="ON"

if [[ "$shared_static" == "static" ]]; then
  shared="OFF"
fi

mkdir -p build
pushd build
  rm -rf *
  cmake .. -DCMAKE_BUILD_TYPE=$buildtype -DBUILD_SHARED_LIBS=$shared "${@:5}" || exit $?
  cmake --build . -- -j4 || exit $?
popd

function deploy()
{
  rm -rf ./build/deploy/*
  cp -rf ./build/$buildtype/bin/* ./build/deploy/
  cp -rfH ./configurations/$prjname/common/* ./build/deploy/ 2>/dev/null || true
  cp -rfH ./configurations/$prjname/$1/* ./build/deploy/ 2>/dev/null || true
  arname="$prjname-$refname-$shared_static-$buildtype-$1.tar.gz"
  tar -zcvf "$arname" -C "./build/deploy/" .
  cp -f "$arname" /monamour/
}

if [ ! -z "$(ls -A ./build/$buildtype/bin/)" ]; then
  mkdir -p build/deploy
  if [[ "$buildtype" == "Release" || "$buildtype" == "RelWithDebInfo" ]]; then
    deploy production
    deploy loads
    deploy stress
  fi
  
  if [[ "$buildtype" == "Debug" || "$buildtype" == "RelWithDebInfo" ]]; then
    deploy devel
  fi 
fi


  
