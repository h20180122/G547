1) make all
2) sudo insmod main.ko
3) ls -l /dev/dof*
4) sudo dd if=/dev/dof of=dof
5) sudo dd if=/dev/zero of=/dev/dof count=1
6) sudo chmod 777 /dev/dof1
7) sudo cat > /dev/dof1
    /* Sample text to be written */
8) sudo xxd /dev/dof1 | less
9) fdisk -l /dev/dof

