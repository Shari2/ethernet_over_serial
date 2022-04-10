SPDX-License-Identifier: BSD-2-Clause
SPDX-FileCopyrightText: Copyright (c) 2022 Marian Sauer

1. wonky patch tty0tty

diff --git a/module/tty0tty.c b/module/tty0tty.c
index 3af0d8b..bf98aa3 100644
--- a/module/tty0tty.c
+++ b/module/tty0tty.c
@@ -273,6 +273,8 @@ static int tty0tty_write(struct tty_struct *tty, const unsigned char *buffer, in
 
 exit:
        up(&tty0tty->sem);
+       if(ttyx)
+           tty_wakeup(tty);
        return retval;
 }

2. build
make
sudo make install

3. load
sudo modprobe tty0tty


4a. linux slip (single hop)
sudo modprobe slip
sudo slattach -p slip /dev/tnt2 &

4b. linux slip (routing)
sudo modprobe slip
sudo slattach -p slip /dev/tnt0 &

5. build
cmake -H. -Bbuild -GNinja
ninja -C ./build

6a. run (single hop)
./build/icmp_server &

6b. run (routing)
./build/icmp_server_dual_interface &
./build/icmp_server &

7a. configure and ping (single hop)
sudo ip addr add 10.1.0.1/16 dev sl0
sudo ip link set dev sl0 up
ping 10.1.0.2

7b. configure and ping (routing)
sudo ip addr add 10.0.0.2/15 dev sl0
sudo ip link set dev sl0 up
ping 10.0.0.1
ping 10.1.0.2

8. test udp
socat -d - UDP4-SENDTO:10.1.0.2:1234
HELLO

# capability to no run as root (tapif_init: /dev/net/tun ioctl TUNSETIFF: Operation not permitted)
sudo setcap cap_net_admin=eip ./build/icmp_server_dual_interface
sudo ip link set dev tun0 up

# set route instead of ip so kernel does not respond to icmp
sudo ip route add 10.0.0.0/15 dev tun0
ping 10.0.0.1


9001. over 9000
plantuml -svg network.plantuml
