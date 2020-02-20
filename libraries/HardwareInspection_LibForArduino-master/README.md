## Environment

Set up the environment.

```
cd {Your ArduinoCore-nRF52840 Path}/ArduinoCore-nRF52840
cd libraries
git clone git@github.com:cami/test_iotpf_hardware.git
cd test_iotpf_hardware
pipenv sync
cd console
python3 main.py
```


## Install NI-VISA driver

https://www.ni.com/ja-jp/support/downloads/drivers/download.ni-visa.html#306042


## Install CP210x USB to UART Bridge VCP Drivers

https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers


## Install PL2303 Mac OS X Driver Download

http://www.prolific.com.tw/US/ShowProduct.aspx?p_id=229&pcid=41


## Install Virtual COM Port Drivers

https://www.ftdichip.com/Drivers/VCP.htm


## Optional: Create .exe file.

```
pyinstaller main.py --clean --name cami-product_board_inspection
pyinstaller cami-product_board_inspection.spec
```

```
a.datas += [('adafruit-nrfutil', 'tools/Adafruit_nRF52_nrfutil/nordicsemi/dist/adafruit-nrfutil', 'Data')]
a.datas += [('nrfjprog', 'tools/nrfjprog/9.4.0/nrfjprog', 'Data')]
a.datas += [('ParentBoard.ino.zip', 'sketches/ParentBoard.ino.zip', 'Data')]
a.datas += [('ChildBoard.ino.zip', 'sketches/ChildBoard.ino.zip', 'Data')]
a.datas += [('nectis_nrf52840_bootloader-6.2.0_s140_6.1.1.hex', 'bootloader/nectis_nrf52840/nectis_nrf52840_bootloader-6.2.0_s140_6.1.1.hex', 'Data')]
```
