/* func_ov130_022999e4 @ 0x022999e4, 0x22 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *);

void func_ov130_022999e4(unsigned char *obj)
{
    int i;
    obj[6] = 0;
    for (i = 0; i < 5; i++) {
        func_02070b84(obj + 0x2c + i * 0x6c);
    }
}
