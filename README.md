# linuxmodule
Creating and testing linux loadable kernel modules.

- Use make to make (duh). 
- insert into the kernel using `sudo insmod <file_name>.ko`
- look at logs `sudo dmesg | tail -10` or `sudo journalctl --system -f` to see `printk` messages.
- logs give a major number for the character device which needs to be created in `\dev`
- create a character device using `sudo mknod c <device_name, mentioned in module> <major_num> <minor_num, 0>`
- `cat \dev\<device_name>` performs a read as implemented in the module
- using root shell, `echo "asdsad" >> \dev\<device_name>` performs a write as implemented in the module
- remove from kernel using `sudo rmmod <file_name>`
