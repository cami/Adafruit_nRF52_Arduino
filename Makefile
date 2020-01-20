.PHONY: flash_softdevice erase

# Flash softdevice
flash_softdevice:
	@echo Flashing: s140_nrf52_6.1.1_softdevice.hex
	nrfjprog -f nrf52 --program ./bootloader/nectis_nrf52840/nectis_nrf52840_bootloader-7.0.0_s140_6.1.1.hex --sectorerase
	nrfjprog -f nrf52 --reset

erase:
	nrfjprog -f nrf52 --eraseall
