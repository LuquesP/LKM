cmd_/home/rpi/src/kernel-dev/kernel/lcd/modules.order := {   echo /home/rpi/src/kernel-dev/kernel/lcd/lcd_driver.ko; :; } | awk '!x[$$0]++' - > /home/rpi/src/kernel-dev/kernel/lcd/modules.order
