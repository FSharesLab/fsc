# Bios Boot Tutorial

The `bios-boot-tutorial.py` script simulates the FSCIO bios boot sequence.

``Prerequisites``:

1. Python 3.x
2. CMake
3. git

``Steps``:

1. Install fscio binaries by following the steps outlined in below tutorial
[Install fscio binaries](https://github.com/FutureSharesCloud/fsc#mac-os-x-brew-install)

2. Install fscio.cdt binaries by following the steps outlined in below tutorial
[Install fscio.cdt binaries](https://github.com/FutureSharesCloud/fscio.cdt#binary-releases)

3. Compile fscio.contracts

```bash
$ cd ~
$ git clone https://github.com/FutureSharesCloud/fscio.contracts.git
$ cd ./fscio.contracts/
$ ./build.sh
$ pwd

```

4. Make note of the directory where the contracts were compiled
The last command in the previous step printed on the bash console the contracts' directory, make note of it, we'll reference it from now on as `FSCIO_CONTRACTS_DIRECTORY`

5. Launch the `bios-boot-tutorial.py` script
Minimal command line to launch the script below, make sure you replace `FSCIO_CONTRACTS_DIRECTORY` with actual directory

```bash
$ cd ~
$ git clone https://github.com/FutureSharesCloud/fsc.git
$ cd ./fsc/tutorials/bios-boot-tutorial/
$ python3 bios-boot-tutorial.py --clfsc="clfsc --wallet-url http://127.0.0.1:6666 " --nodfsc=nodfsc --kfscd=kfscd --contracts-dir="/FSCIO_CONTRACTS_DIRECTORY/" -a

```

See [FSCIO Documentation Wiki: Tutorial - Bios Boot](https://github.com/FutureSharesCloud/fsc/wiki/Tutorial-Bios-Boot-Sequence) for additional information.
