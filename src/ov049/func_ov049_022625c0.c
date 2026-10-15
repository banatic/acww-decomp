/* func_ov049_022625c0 @ 0x022625c0, 0x34 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, unsigned short i, int j);

int func_ov049_022625c0(void *arg)
{
    func_02019d0c((char *) arg + 0x564, 10, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
