# Zaber 
C++ interface for Zaber family stages. Currently only supports single axis stages (X-LSQ & X-RSW). 

## Prerequisites
* [cmake](https://cmake.org/)

## Build
```
mkdir build
cd build
cmake ..
make
```

## Running stage tests:
Please ensure the stage is connected and your serial port matches the device. 
```
sudo ./bin/zaber_X_LSQ_test 
sudo ./bin/zaber_X_RSW_test 
```

## Currently supported devices: ##
* [X-RSW-E Rotary Stage](https://www.zaber.com/products/rotary-stages/X-RSW-E)
* [X-LSQ linear stage](https://www.zaber.com/products/linear-stages/X-LSQ)

## TODOs ##
* Support multi axis devices. 
* Support binary protocol.


## Relevant Reading ##
* [ASCII Protocol Manual](https://www.zaber.com/wiki/Manuals/ASCII_Protocol_Manual)
* [X-RSW-E Command reference](https://www.zaber.com/manuals/-RSW-E#9-quick-command-reference)

