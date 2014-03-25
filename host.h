#ifndef HOST_H
#define HOST_H
#include <string.h>


/*
 *Reference: http://albert-oma.blogspot.tw/2012/04/semihosting.html
 */
enum HOST_SYSCALL{
	SYS_OPEN=0x01,
	SYS_CLOSE,
	SYS_WRITEC,
	SYS_WRITE0,
	SYS_WRITE,
	SYS_READ,
	SYS_READC,
	SYS_ISERROR,
	SYS_ISTTY,
	SYS_SEEK,
	SYS_FLEN=0xC,
	SYS_TMPNAM,
	SYS_REMOVE,
	SYS_RENAME,
	SYS_CLOCK,
	SYS_TIME,
	SYS_SYSTEM,
	SYS_ERRNO,
	SYS_GET_CMDLINE=0x15,
	SYS_HEAPINFO,
	SYS_ELAPSED=0x30,
	SYS_TICKFREQ
};

enum HOST_OPEN{
	HO_RONLY = 0x01,
	HO_RBONLY,
	HO_RPONLY,
	HO_RPBONLY,
	HO_WONLY,
	HO_WBONLY,
	HO_WPONLY,
	HO_WPBONLY,
	HO_APPEND,
	HO_APPENDB,
	HO_APPENDP,
	HO_APPENDPB
};

int host_call(enum HOST_SYSCALL, void *argv) __attribute__((naked));

int host_system(char *cmd);
int host_open(char *file, enum HOST_OPEN);
#endif 
