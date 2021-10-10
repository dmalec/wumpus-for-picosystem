# wumpus-for-picosystem
Wumpus for the Pimoroni PicoSystem

# Pico SDK Build Environment
```
git clone https://github.com/raspberrypi/pico-sdk.git ~/pico-sdk
cd ~/pico-sdk
git submodule update --init
export PICO_SDK_PATH="~/pico-sdk"
```

# PicoSystem SDK Build Environment
```
git clone https://github.com/pimoroni/picosystem.git ~/picosystem
mkdir ~/picosystem/build

cd ~/picosystem/build && \
cmake -DPICOSYSTEM_DIR:PATH=~/picosystem .. && \
make
```

# Building Wumpus for the Pimoroni PicoSystem
```
git clone git@github.com:dmalec/wumpus-for-picosystem.git
cd wumpus-for-picosystem
mkdir build
cd build
cmake -DPICOSYSTEM_DIR:PATH=~/picosystem ..
make
```
