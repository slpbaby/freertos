#include "host.h"

typedef union param_t{
	int pdInt;
	void *pdPtr;
	char *pdChrPtr;
} param;


/*action will be in r0, and argv in r1*/
int host_call(enum HOST_SYSCALL action, void *argv)
{
    /* For Thumb-2 code use the BKPT instruction instead of SWI.
* Refer to:
* http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0471c/Bgbjhiea.html
* http://en.wikipedia.org/wiki/ARM_Cortex-M#Cortex-M4 */
    int result;
    __asm__( \
      "bkpt 0xAB\n"\
      "nop\n" \
      "bx lr\n"\
        :"=r" (result) ::\
    );
    return result;
}

int host_system(char *cmd){
	return host_call(SYS_SYSTEM, (param []){{.pdChrPtr=cmd}, {.pdInt=strlen(cmd)}});
}

int host_open(char *file, enum HOST_OPEN mode){
	return host_call(SYS_OPEN, (param []){{.pdChrPtr=file}, {.pdInt=strlen(file)}, {.pdInt=mode}});
}

int host_close(int handle){
	return host_call(SYS_CLOSE, (param []){{.pdInt=handle}});
}

int host_write(int handle, char *buffer){
	return host_call(SYS_WRITE, (param []){{.pdInt=handle}, {.pdChrPtr=buffer}, {.pdInt=strlen(buffer)}});
}

int write_to_host_file(char *file, char *buffer, int append) {
	
	int HostHandle;
	if (append == 1) 
		HostHandle = host_open(file,HO_APPEND);
	else 
		HostHandle = host_open(file,HO_WONLY);
	if (HostHandle == -1)
		return -1;
	host_write(HostHandle,buffer);
	host_close(HostHandle);
	return 0;
}
