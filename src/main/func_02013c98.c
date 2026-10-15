/* func_02013c98 @ 0x02013c98, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(void *ptr);
extern int func_02019de8(void *ptr);
extern int func_02019d0c(void *ptr, int a, int b, int c, int d, int e, int f, int g, int h, unsigned int i, int j);
extern unsigned short data_020c80f8;

void func_02013c98(unsigned char *param0, unsigned char *param1)
{
    if (func_02019e00(param1 + 0x564) == 7 && func_02019de8(param1 + 0x564) != 0) {
        func_02019d0c(param1 + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        if (param0[0xb] == 1) {
            *(unsigned int *) (param1 + 0x4e8) &= ~2;
        }
        param0[0xa] = 1;
        param0[0x8] = 5;
    }
}
