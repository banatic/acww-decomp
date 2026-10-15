/* func_02039d98 @ 0x02039d98, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d368(void);
extern void RtcSendPxiCommand(int);

void func_02039d98(void *self)
{
    int r4;
    int r1;
    int r0;
    int *p;
    unsigned char *pb;

    r4 = 0;
    r1 = 0;
    p = (int *) ((char *) self + 0xa4);
    *p = 1;
    pb = (unsigned char *) ((char *) self + 0xb4);
    *pb = 1;
    if (*(int *) ((char *) self + 0xc) == 0) {
        asm {
            ldr r0, =0x136
            mov r1, #2
        }
        r0 = func_0209d368();
        r4 = r0 + 3;
    } else {
        asm {
            ldr r0, =0x12c
            mov r1, #2
        }
        r0 = func_0209d368();
        r4 = r0 + 3;
    }
    if (*(int *) ((char *) self + 0xc) == 0) {
        asm {
            ldr r0, =0x136
            mov r1, #3
        }
        r0 = func_0209d368();
        r1 = r0 + 5;
    } else {
        asm {
            ldr r0, =0x12c
            mov r1, #3
        }
        r0 = func_0209d368();
        r1 = r0 - 5;
    }
    p = (int *) ((char *) self + 0xa8);
    *p = r4;
    *(int *) ((char *) self + 0x4c) = r1;
    if (*(int *) ((char *) self + 0xc) != 0) {
        RtcSendPxiCommand(0x3f);
    }
}
