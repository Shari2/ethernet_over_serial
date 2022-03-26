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


4. linux slip
sudo modprobe slip
sudo slattach -p slip /dev/tnt0 &

5. build and run
cmake -H. -Bbuild -GNinja
ninja -C ./build

./build/icmp_server &

6. configure and ping
sudo ip addr add 10.0.0.1/24 dev sl0
sudo ip link set dev sl0 up

ping 10.0.0.2


9001. over 9000
plantuml -svg network.plantuml
