#!/bin/bash

NATIVECONFIGDIR="/home/developer/Downloads/eclipse/workspace/JNISample/jni/buildkit/linux64"
NATIVESOURCEDIR="/home/developer/Downloads/eclipse/workspace/JNISample/jni"
NATIVEBINDIR="/home/developer/Downloads/eclipse/workspace/JNISample/jni/bin/linux64"
ISOSDKCOREDIR="/home/developer/Downloads/eclipse/workspace/JNISample/jni/isosdk/lib/linux64"
JARLIBDIR="/home/developer/Downloads/eclipse/workspace/JNISample/jar/jni/linux64"

# -- CMake configure
cmake -B $NATIVECONFIGDIR -S $NATIVESOURCEDIR -D PATH_TO_ISOSDK=$NATIVESOURCEDIR

cd $NATIVECONFIGDIR
make 

# -- Copy 64bit Files
cp $ISOSDKCOREDIR/libIsoSDKCore64.2.31.so $JARLIBDIR
cp $NATIVECONFIGDIR/libIsoSDKJNI.so $JARLIBDIR
