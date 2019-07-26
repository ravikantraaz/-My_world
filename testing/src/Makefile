#uncomment below for IMX6
#export PATH=/opt/freescale-imx6/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games

#uncomment below for IMX25
export PATH=/opt/freescale-31/usr/local/gcc-4.1.2-glibc-2.5-nptl-3/arm-none-linux-gnueabi/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games

#export PATH=/opt/freescale-35/usr/local/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games

#uncomment below for IMX6/25 GNOME
CC=arm-none-linux-gnueabi-gcc
#uncomment below for IMX25/QT
#CC=arm-fsl-linux-gnueabi-gcc

INCLUDE=-I ../inc
LIB=-L ../lib -lgl11pos -ltfm -liengine_ansi_iso
OBJ=main.o enroll.o init_fp.o optcap.o iodev.o deinit_fp.o

all:$(OBJ)
	$(CC) -o Sample $(OBJ) $(LIB)
	@rm -rf *.o
	@ctags -R ../*
main.o:main.c
	$(CC) -c main.c $(INCLUDE) -o main.o
optcap.o:optcap.c
	$(CC) -c optcap.c $(INCLUDE) -o optcap.o
init_fp.o:init_fp.c
	$(CC) -c init_fp.c $(INCLUDE) -o init_fp.o
enroll.o:enroll.c
	$(CC) -c enroll.c $(INCLUDE) -o enroll.o
deinit_fp.o:deinit_fp.c
	$(CC) -c deinit_fp.c $(INCLUDE) -o deinit_fp.o
iodev.o:iodev.c
	$(CC) -c iodev.c $(INCLUDE) -o iodev.o
clean:
	rm -rf *.o  Sample tags
