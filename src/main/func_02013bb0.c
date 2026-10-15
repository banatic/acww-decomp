/* func_02013bb0 @ 0x02013bb0, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200443c(int receiver, unsigned short value);
extern int func_020b1cb0(void *ptr);

void func_02013bb0(unsigned char *data, void *param)
{
    unsigned int flags = *(unsigned int *) ((char *) param + 0xb0);
    unsigned int cond;

    cond = (flags & 4) ? 1 : 0;
    if (cond > 0) {
        cond = (flags & 2) ? 1 : 0;
        if (cond > 0) {
            return;
        }
    }

    if (*data != 0) {
        int value = func_020b1cb0((char *) param + 0x5c);
        asm {
            add r1, value, #0
            ldr r0, =0x514
            add r0, param, r0
            mov r2, #0
            bl func_0200443c
        }
    }
}
