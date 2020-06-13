µCOS Example App
================

This is an example application using µCOS III and its TCP/IP stack
on the i.MX6UL processor.

It is compiled using the GNU toolchain.

Development Environment
-----------------------
TBD

Required Tools
--------------
The first step to build this App is to install the required packages:

**Development tools**
```bash
$ sudo apt-get install make gcc-arm-linux-gnueabi
```
**Qemu**
```bash
$ sudo apt-get install qemu-system-arm
```

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
***
Copyright 2020 Silicon Labs

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
***
