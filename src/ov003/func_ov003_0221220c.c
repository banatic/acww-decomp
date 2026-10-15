/* func_ov003_0221220c @ 0x0221220c, 0x64 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_022122a0(void *, int *, unsigned char);
extern void func_ov003_0221228c(void *, unsigned char, unsigned char, unsigned char, unsigned char);
extern void func_020109a0(void *, int b, int c, unsigned short d);
extern unsigned int *func_0200f27c(void *, int);

void func_ov003_0221220c(void *self, void *data, int previous)
{
    unsigned char *p = (unsigned char *) data + 0xc;
    unsigned char c = p[2];
    int b0 = p[0];
    int b1 = p[1];
    int loc[2];

    loc[0] = b0;
    loc[1] = b1;
    func_ov003_022122a0((char *) self + 0x7d4, loc, c);
    func_ov003_0221228c((char *) self + 0x8f0, c, (unsigned char) b0, (unsigned char) b1, ((unsigned char *) self)[0x16c]);
    func_020109a0(self, 0x4c, 3, 0);
    if (c != 0) {
        func_0200f27c(self, 0x1c);
    }
}
