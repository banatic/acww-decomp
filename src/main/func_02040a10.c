/* func_02040a10 @ 0x02040a10, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_0209ded0(void);
extern unsigned char *func_02040980(void);
extern void func_020409e8(void);

void func_02040a10(unsigned char *param)
{
    unsigned char val;
    unsigned char *p;
    unsigned char b2;
    unsigned char b13;

    val = func_0209ded0();
    asm { add r0, param, #0 }
    p = func_02040980();
    if (p != 0) {
        b2 = p[2];
        b13 = param[0x13];
        if (val != b13 || b2 != param[0x12]) {
            param[0x12] = b2;
            param[0x13] = val;
        }
        asm { add r0, param, #0 }
        func_020409e8();
    }
}
