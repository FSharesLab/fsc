#!/bin/bash
##########################################################################
# This is the FSCIO automated install script for Linux and Mac OS.
# This file was downloaded from https://github.com/FutureSharesCloud/fsc
#
# Copyright (c) 2017, Respective Authors all rights reserved.
#
# After June 1, 2018 this software is available under the following terms:
# 
# The MIT License
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
# https://github.com/FutureSharesCloud/fsc/LICENSE.txt
##########################################################################

if [ "$(id -u)" -ne 0 ]; then
        printf "\n\tThis requires sudo. Please run with sudo.\n\n"
        exit -1
fi   

   CWD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
   if [ "${CWD}" != "${PWD}" ]; then
      printf "\\n\\tPlease cd into directory %s to run this script.\\n \\tExiting now.\\n\\n" "${CWD}"
      exit 1
   fi

   BUILD_DIR="${PWD}/build"
   CMAKE_BUILD_TYPE=Release
   TIME_BEGIN=$( date -u +%s )
   INSTALL_PREFIX="/usr/local/fscio"
   VERSION=1.2

   txtbld=$(tput bold)
   bldred=${txtbld}$(tput setaf 1)
   txtrst=$(tput sgr0)

   create_symlink() {
      pushd /usr/local/bin &> /dev/null
      ln -sf ../fscio/bin/$1 $1
      popd &> /dev/null
   }

   create_cmake_symlink() {
      mkdir -p /usr/local/lib/cmake/fscio
      pushd /usr/local/lib/cmake/fscio &> /dev/null
      ln -sf ../../../fscio/lib/cmake/fscio/$1 $1
      popd &> /dev/null
   }

   install_symlinks() {
      printf "\\n\\tInstalling FSCIO Binary Symlinks\\n\\n"
      create_symlink "clfsc"
      create_symlink "fscio-abigen"
      create_symlink "fscio-launcher"
      create_symlink "fscio-s2wasm"
      create_symlink "fscio-wast2wasm"
      create_symlink "fsciocpp"
      create_symlink "kfscd"
      create_symlink "nodfsc"
   }

   if [ ! -d "${BUILD_DIR}" ]; then
      printf "\\n\\tError, fscio_build.sh has not ran.  Please run ./fscio_build.sh first!\\n\\n"
      exit -1
   fi

   ${PWD}/scripts/clean_old_install.sh
   if [ $? -ne 0 ]; then
      printf "\\n\\tError occurred while trying to remove old installation!\\n\\n"
      exit -1
   fi

   if ! pushd "${BUILD_DIR}"
   then
      printf "Unable to enter build directory %s.\\n Exiting now.\\n" "${BUILD_DIR}"
      exit 1;
   fi
   
   if ! make install
   then
      printf "\\n\\t>>>>>>>>>>>>>>>>>>>> MAKE installing FSCIO has exited with the above error.\\n\\n"
      exit -1
   fi
   popd &> /dev/null 

   install_symlinks   
   create_cmake_symlink "fscio-config.cmake"

   printf "\n\n${bldred}\n"
   printf "\t _______    _______    _______   _________    _______ \n"
   printf "\t(  ____ \  (  ____ \  (  ____ \  \\__   __/   (  ___  )\n"
   printf "\t| (    \/  | (    \/  | (    \/     ) (      | (   ) |\n"
   printf "\t| (____    | (_____   | |           | |      | |   | |\n"
   printf "\t|  ____)   (_____  )  | |           | |      | |   | |\n"
   printf "\t| (              ) |  | |           | |      | |   | |\n"
   printf "\t| (        /\____) |  | (____/\  ___) (___   | (___) |\n"
   printf "\t(_)        \_______)  (_______/  \_______/   (_______)\n${txtrst}"

   printf "\\tFor more information:\\n"
   printf "\\tFSCIO website: https://www.fshares.io\\n"