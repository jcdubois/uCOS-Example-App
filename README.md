uCOS-Example-App
================

This is an example application using µCOS III and its TCP/IP stack
on the i.MX6UL processor.

It is compiles using the GNU toolchain.

Development Environment
-----------------------
TBD

Required Tools
--------------
TBD


Build
-----

To build this example:

```bash
$ cd /app/base/directory/
$ make
```

Deploy
------

This application should be able to run on the real i.MX6UL development
board. However it does also run inside Qemu.

**Qemu**
```bash
$ qemu-system-arm -machine mcimx6ul-evk -m 128M -display none -serial mon:stdio -kernel ./OS.elf
```

References
----------
TBD

License
-------
TBD
