cmd_/home/rpi/src/kernel-dev/kernel/read_write/Module.symvers := sed 's/\.ko$$/\.o/' /home/rpi/src/kernel-dev/kernel/read_write/modules.order | scripts/mod/modpost -m -a  -o /home/rpi/src/kernel-dev/kernel/read_write/Module.symvers -e -i Module.symvers   -T -