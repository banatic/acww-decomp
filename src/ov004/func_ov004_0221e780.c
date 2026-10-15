/* func_ov004_0221e780 @ 0x0221e780, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern int func_02019c6c(void *, int, unsigned short);
extern unsigned short data_020c80f8;

void func_ov004_0221e780(void *a0, char *a1)
{
    if (func_02019e00(a1 + 0x564) == 3) {
        if (func_02019de8(a1 + 0x564) != 0) {
            func_02019c6c(a1 + 0x564, 2, data_020c80f8);
            ((unsigned char *) a0)[0xc] = 1;
        }
    }
}
