/* func_0209bf80 @ 0x0209bf80, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_0209c410(unsigned char *p, unsigned char c);
extern void func_0209c448(unsigned char *p, unsigned char a, unsigned char b);
extern void func_0209c52c(unsigned char *p);

extern unsigned char data_020d1a38[];

void func_0209bf80(unsigned char *base, short *arr)
{
    unsigned char *gp = (unsigned char *) data_020d1a38;
    int k = 0;
    int i;
    for (i = 0; i < 8; i++) {
        int r = func_0209c410(base + 0x19, (unsigned char) i);
        if (*gp != 0 && r != 0) {
            short val = arr[k];
            int t = (val * *gp * r) >> 12;
            func_0209c448(base + 0x11, (unsigned char) i, (unsigned char) t);
        }
        arr++;
        gp++;
    }
    func_0209c52c(base + 0x19);
}
