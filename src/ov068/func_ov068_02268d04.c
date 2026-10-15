/* func_ov068_02268d04 @ 0x02268d04, 0x50 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *ptr);
extern int func_0203b144(void);
extern int func_02019d0c(void *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11);
extern unsigned short data_020c80f8;

void func_ov068_02268d04(void *self, void *base)
{
    if (func_02014868((char *) base + 0x618) != 0) {
        return;
    }
    func_0203b144();
    func_02019d0c((char *) base + 0x564, 3, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    *(unsigned char *) ((char *) self + 0x1c) = 1;
}
