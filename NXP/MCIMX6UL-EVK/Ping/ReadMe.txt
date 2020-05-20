TCPIP EXAMPLE FOR THE NXP i.MX6 UltraLite, REVISION C2

This example project demonstrates how to initialize uC/TCPIP.

MICRIUM PRODUCT VERSIONS
- uC/OS-III   v3.07.03
- uC/CPU      v1.31.04
- uC/LIB      v1.38.02
- uC/Common   v1.01.00
- uC/TCPIP    v3.05.00
- uC/DHCPc    v2.10.01

IDE/COMPILER VERSIONS
- IAR/EWARM v8.20.1

HARDWARE SETUP
- Remove resistors R1407, R1431, R1432, R1433, and R1434
- Connect J-Link debugger into JTAG port
- Connect an Ethernet cable from your local network into the board's ENET 1 port (J1501A)
- Optional: Connect an Ethernet cable from your local network into the board's ENET 2 port (J1501B)
- Connect power chord and turn the switch SW2001 to the 'on' position

WORKSPACE LOCATIONS
- NXP\MCIMX6UL-EVK\Ping\OS3\IAR\Ping.eww

BUILD CONFIGURATIONS
- Several build configurations are available with this project:
    library     A partial source build that links with the library NXP\MCIMX6UL-EVK\Ping\OS3\IAR\Ping.a
    libgen      A full source build that outputs a library file.
    source      A full source build that generates an executable

USAGE INSTRUCTIONS
- Open the workspace in IAR.
- The project uses DHCP by default to configure an IP addresses to the interface(s), but if a static IPv4 address is desired make sure to modify 
the following '#defines' in app_cfg.h:
    (if APP_CFG_ENET1_EN is set to DEF_ENABLED)
    #define  APP_CFG_TCPIP_ENET1_IP_ADDR_IPv4
    #define  APP_CFG_TCPIP_ENET1_SUBNET_MASK_IPv4
    #define  APP_CFG_TCPIP_ENET1_DFLT_GATEWAY_IPv4

    (if APP_CFG_ENET2_EN is set to DEF_ENABLED)
    #define  APP_CFG_TCPIP_ENET2_IP_ADDR_IPv4
    #define  APP_CFG_TCPIP_ENET2_SUBNET_MASK_IPv4
    #define  APP_CFG_TCPIP_ENET2_DFLT_GATEWAY_IPv4

    #define  APP_CFG_DHCPc_EN   DEF_DISABLED

    Note: If DHCPc is enabled, the board will temporarily assign these static IP addresses which will eventually be overwritten once a response 
from the server is received. However, if the server fails to respond, a link-local address in the 169.254.x.x range will be assigned to each
enabled interface.
    Note: The Hardware (MAC) address for each interface are configured in net_dev_cfg.c.

- Press F7 to build the project and Ctrl+D to start the debug session.
- Depending on the J-Link driver version, the user might be prompted to select the device from a list of recognized
  devices. Please select the ARM Cortex A7 core from the list.
- Once the debug session has started, select "View->Terminal I/O" from the menu and press F5 to run the example.
    Note: If the project is opened with IAR v8.30.1 or higher, the semihosted IAR printf() appears to have a bug in its implementation where
    the output does not immediately show up in the Terminal I/O view as it did in previous versions. Instead, the execution stops and at the
    Disassembly View the program executes the [CTRL_C1_W + 0] instruction before printf() finishes outputting the characters. We observed that if 
    one steps through the program (F10) after this occurs, the characters eventually make it to the Terminal I/O window. We contacted IAR and they
    are now aware of this problem. (See forum post https://www.micrium.com/forums/topic/nxp-mcimx6ul-evk-ping/#post-25796 for more details).
- The uC/TCPIP stack will initialize with the configured static IP address.
- Once an IP is assigned to the board, you may ping the board from a PC's command line to verify if it is running.


Please feel free to post questions or comments related to this example project at Micrium's forum page:

https://www.micrium.com/forums/topic/nxp-mcimx6ul-evk-ping/