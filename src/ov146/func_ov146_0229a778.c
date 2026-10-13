/* func_ov146_0229a778 @ 0x0229a778, 0x2c bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov146_0229a578(void *);
extern void func_ov002_022080a0(void *, int);

void func_ov146_0229a778(void *param)
{
    if (((volatile unsigned char *) param)[0xba] != 0) {
        ((volatile unsigned char *) param)[0xba] = ((volatile unsigned char *) param)[0xba] - 1;
    } else {
        func_ov146_0229a578(param);
        func_ov002_022080a0(param, 1);
    }
}
