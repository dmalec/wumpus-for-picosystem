Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/focal64"

  config.vm.provision "shell", inline: <<-SHELL
    apt-get update
    apt-get upgrade -y

    # pico requirements
    apt-get -y install build-essential \
                       cmake \
                       gcc-arm-none-eabi \
                       libnewlib-arm-none-eabi \
                       libstdc++-arm-none-eabi-newlib
  SHELL

  config.vm.provision "shell", privileged: false, env: {"PICO_SDK_PATH" => "~vagrant/pico-sdk"}, inline: <<-SHELL
    # pico sdk
    git clone https://github.com/raspberrypi/pico-sdk.git ~/pico-sdk
    echo 'export PICO_SDK_PATH="~vagrant/pico-sdk"' >> ~/.bashrc
    cd ~/pico-sdk && \
      git submodule update --init

    # pico system
    git clone https://github.com/pimoroni/picosystem.git ~/picosystem
    mkdir ~/picosystem/build

    cd ~/picosystem/build && \
      cmake -DPICOSYSTEM_DIR:PATH=~/picosystem .. && \
      make

  SHELL
end
