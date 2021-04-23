# NucleoF446RE_tinyshell_nos
A simple Shell application using NucleoF446RE

Sometimes it is useful to interact with a firmware using a shell.
For example, in the case of communication test between the microcontroller and an external component, or in the case of unit test.
This repo is an example of a minimalist shell implementation that has been developed on interrupt.memfault.com.
https://interrupt.memfault.com/blog/firmware-shell

The port on a NucleoF446RE has been done with STM32CubeIDE and the HAL library.
This version uses a UART device in DMA mode to communicate with a serial terminal. 
There is also another implementation using FreeRTOS in the following repo:
https://github.com/rreicher/NucleoF446RE_tinyshell_os
