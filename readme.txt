SPDX-License-Identifier: BSD-2-Clause
SPDX-FileCopyrightText: Copyright (c) 2022 Marian Sauer


1. build
cmake -H. -B./build_pc -GNinja -DCMAKE_BUILD_TYPE=DEBUG -DCMAKE_TOOLCHAIN_FILE=./target/pc/gcc_x86_32bit.cmake
ninja -C ./build_pc

cmake -H. -B./build_openmote -GNinja -DCMAKE_BUILD_TYPE=DEBUG -DCMAKE_TOOLCHAIN_FILE=./target/openmote_CC2538_REV_A1/openmote_cc2528_rev_a1.cmake
ninja -C ./build_openmote

2. run (mote should be ttyUSB0)
ninja -C ./build_openmote flash_cc2538_with_icmp_server

sudo setcap cap_net_admin=eip ./build_pc/icmp_server_dual_interface
./build_pc/icmp_server_dual_interface &

# icmp_server_dual_interface needs cap_net_admin to setup tun/tap and set route
# icmp_server_dual_interface will setup tun interface with a route instead of ip so kernel will not handle icmp


3. ping
ping 10.0.0.1
ping 10.1.0.2

4. test udp echo
socat -d - UDP4-SENDTO:10.1.0.2:1234
HELLO


9001. over 9000
plantuml -svg network.plantuml
