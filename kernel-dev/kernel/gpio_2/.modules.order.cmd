cmd_/home/rpi/src/kernel-dev/kernel/gpio_2/modules.order := {   echo /home/rpi/src/kernel-dev/kernel/gpio_2/gpio_2.ko; :; } | awk '!x[$$0]++' - > /home/rpi/src/kernel-dev/kernel/gpio_2/modules.order
