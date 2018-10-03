# Zaber 
C++ interface for Zaber family stages. Currently only one stage is supported. This project is still under development and in its early days so everything is subject to change. .

## Prerequisites
* [cmake](https://cmake.org/)

## Build
```
mkdir build
cd build
cmake ..
make
```

## Running examples:
```
./bin/zaber_app --help
```

## Currently supported devices: ##
* [X-RSW-E Rotary Stage](https://www.zaber.com/products/rotary-stages/X-RSW-E)

## TODOs ##
* Support multi axis devices. 
* Support binary protocol.
* Support multiple devices (chain configuration)


## Relevant Reading ##
* [ASCII_Protocol_Manual](https://www.zaber.com/wiki/Manuals/ASCII_Protocol_Manual)
* [X-RSW-E Command reference](https://www.zaber.com/manuals/-RSW-E#9-quick-command-reference)

