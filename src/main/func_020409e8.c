/* func_020409e8 @ 0x020409e8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021c7580;
extern unsigned char data_021f39c0[];
extern unsigned char *func_02040980(void);

void func_020409e8(void)
{
    unsigned char *p;
    data_021c7580 = 0xff;
    asm { ldr r0, =data_021f39c0 }
    p = func_02040980();
    if (p != 0) {
        data_021c7580 = p[5];
    }
}
