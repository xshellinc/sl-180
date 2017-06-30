# SL-180


# Software Installation

## Raspberry Pi

Make sure to use Raspbian.

### Install Node.js

```
curl -sL https://deb.nodesource.com/setup_7.x | sudo -E bash -
sudo apt-get install -y nodejs
```

### Set up i2c

Uncomment line:46 in `/boot/config.txt`.
```
dtparam=i2c_arm=on
```

Add following lines to `/etc/modules`
```
i2c-bcm2708
i2c-dev
```

reboot OS.
```
reboot
```

### Set up Bluetooth

You may need to stop bluetoothd for prevent interference.
```
sudo systemctl stop bluetooth
sudo systemctl disable bluetooth
```

Install bluetooth libraries.
```
sudo apt-get install bluetooth bluez libbluetooth-dev libudev-dev
```

To power bluetooth adapter up.
```
sudo hciconfig hci0 up
```

### Installation

Clone sl-180 repository:
```
git clone https://github.com/xshellinc/sl-180.git
```

The repository inclueds source code for Raspberry Pi, iOS and Arduino.
Move to raspberry directory and install dependencies:
```
cd <PATH TO SL-180>/raspberry/
npm install
```

then, you can start the application with:
```
sudo node index.js
```
