
1.1 - fully update your operating system.
sudo apt update && sudo apt upgrade -y
1.2 - Download and install the essential packages to compile kernels
.sudo apt install build-essential libncurses-dev libssl-dev libelf-dev bison flex -y
.sudo apt install vim -y
1.3 - Clean up your installed packages.
sudo apt clean && sudo apt autoremove -y
1.4 - Download the source code of the latest stable version of the Linux kernel
wget -P ~/ https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.8.1.tar.xz
1.5 - Unpack the tarball you just downloaded to your home folder.
tar -xvf ~/linux-5.8.1.tar.xz -C ~/
1.6 - Reboot your computer.
2.1 - Check the version of your current kernel.
uname -r
2.2 - Change your working directory to the root directory of the recently unpacked source code.
cd ~/linux-5.8.1/
2.3 - Create the home directory of your system call.
mkdir identity
2.4 - Create a C file for your system call.
nano identity/identity.c
Write the following code in it.
#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE0(identity)

{
    printk("I am Jihan Jasper Al-rashid.\n");
    return 0;
}
2.5 - Create a Makefile for your system call.
.nano identity/Makefile
.obj-y := identity.o
2.6 - Add the home directory of your system call to the main Makefile of the kernel.
nano Makefile
Add the home directory of your system call at the end like the following.
kernel/ certs/ mm/ fs/ ipc/ security/ crypto/ block/ identity/
2.7 - Add a corresponding function prototype for your system call to the header file of system calls.
nano include/linux/syscalls.h
Navigate to the bottom of it and write the following code just above #endif.
asmlinkage long sys_identity(void);
2.8 - Add your system call to the kernel's system call table.
nano arch/x86/entry/syscalls/syscall_64.tbl
Navigate to the bottom of it. You will find a series of x32 system calls. Scroll to the section above it. This is the section of your interest. Add the following code at the end of this section respecting the chronology of the row as well as the format of the column. Use Tab for space.
440     common  identity                sys_identity
3.1 - Configure the kernel.
make menuconfig
3.2 - Find out how many logical cores you have.
nproc
3.3 - Compile the kernel's source code.
make -j12
3.4 - Prepare the installer of the kernel.
sudo make modules_install -j12
3.5 - Install the kernel.
sudo make install -j12
3.6 - Update the bootloader of the operating system with the new kernel.
sudo update-grub
4.1 - Check the version of your current kernel.
uname -r
4.2 - Change your working directory to your home directory.
cd ~
Create the C file with the following command.
nano report.c
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define __NR_identity 440

long identity_syscall(void)
{
    return syscall(__NR_identity);
}

int main(int argc, char *argv[])
{
    long activity;
    activity = identity_syscall();

    if(activity < 0)
    {
        perror("Sorry, Jasper. Your system call appears to have failed.");
    }

    else
    {
        printf("Congratulations, Jasper! Your system call is functional. Run the command dmesg in the terminal and find out!\n");
    }

    return 0;
}
4.4 - Compile the C file you just created.
gcc -o report report.c
- Run the C file you just compiled.
./report
4.6 - Check the last line of the dmesg output.
dmesg
Congratulations! You have successfully added a system call to the Linux kernel!
