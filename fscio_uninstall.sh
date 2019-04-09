#! /bin/bash

binaries=(clfsc
          fscio-abigen
          fscio-launcher
          fscio-s2wasm
          fscio-wast2wasm
          fsciocpp
          kfscd
          nodfsc
          fscio-applesdemo)

if [ -d "/usr/local/fscio" ]; then
   printf "\tDo you wish to remove this install? (requires sudo)\n"
   select yn in "Yes" "No"; do
      case $yn in
         [Yy]* )
            if [ "$(id -u)" -ne 0 ]; then
               printf "\n\tThis requires sudo, please run ./fscio_uninstall.sh with sudo\n\n"
               exit -1
            fi

            pushd /usr/local &> /dev/null
            rm -rf fscio
            pushd bin &> /dev/null
            for binary in ${binaries[@]}; do
               rm ${binary}
            done
            # Handle cleanup of directories created from installation
            if [ "$1" == "--full" ]; then
               if [ -d ~/Library/Application\ Support/fscio ]; then rm -rf ~/Library/Application\ Support/fscio; fi # Mac OS
               if [ -d ~/.local/share/fscio ]; then rm -rf ~/.local/share/fscio; fi # Linux
            fi
            popd &> /dev/null
            break;;
         [Nn]* )
            printf "\tAborting uninstall\n\n"
            exit -1;;
      esac
   done
fi
