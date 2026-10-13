/* func_0209b0f4 @ 0x0209b0f4, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern void func_0209b23c(unsigned char *);
extern void func_0209bd30(unsigned char *, int, unsigned short *, int);
extern unsigned int func_0209b184(unsigned char *, unsigned char);
extern void func_0209b160(unsigned char *, unsigned int);
extern unsigned short data_020d1a28[];

void func_0209b0f4(unsigned char *p)
{
    unsigned short local;
    unsigned int tmp;
    int i;
    tmp = func_020644cc(10) & 1;
    func_0209b23c(p);
    local = data_020d1a28[tmp];
    func_0209bd30(p, 20, &local, 0);
    for (i = 0; i < 5; i++) {
        p[13] |= 1 << i;
    }
    tmp = func_0209b184(p, p[13]);
    if (tmp < 5) {
        func_0209b160(p, tmp);
        p[12] = (unsigned char) tmp;
    }
}
