/* func_ov003_02218e4c @ 0x02218e4c, 0x60 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02218eb8(void *, void *);
extern void func_020109fc(void *, int, int, int);
extern int func_0200fbe0(void *);
extern void func_0205eae0(void *, int, int, int);

void func_ov003_02218e4c(void *self, void *data, int previous)
{
    unsigned char *p = (unsigned char *) data + 0xc;
    unsigned char b0 = p[0];
    unsigned char b1 = p[1];
    unsigned char *dst = (unsigned char *) self + 0x7d4;
    int loc[2];

    dst[0] = b0;
    dst[1] = b1;
    dst[2] = 0;
    loc[0] = b0;
    loc[1] = b1;
    func_ov003_02218eb8((unsigned char *) self + 0x8f0, loc);
    func_020109fc(self, 0x15, 3, 0);
    if (func_0200fbe0(self) == 4) {
        func_0205eae0((unsigned char *) self + 0x5a0, 0xb, 3, 0);
    }
}
