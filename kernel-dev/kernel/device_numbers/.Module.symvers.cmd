cmd_/home/rpi/src/kernel-dev/kernel/device_numbers/Module.symvers := sed 's/\.ko$$/\.o/' /home/rpi/src/kernel-dev/kernel/device_numbers/modules.order | scripts/mod/modpost -m -a  -o /home/rpi/src/kernel-dev/kernel/device_numbers/Module.symvers -e -i Module.symvers   -T -