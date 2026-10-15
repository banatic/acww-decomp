/* func_020c2ca4 @ 0x020c2ca4, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_02013c04(void *p);

int func_020c2ca4(void *self)
{
    func_02019d0c((char *) self + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    *(unsigned char *) ((char *) self + 0x651) = 0;
    func_02013c04((char *) self + 0x558);
    return 1;
}
