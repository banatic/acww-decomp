/* func_ov003_02216a00 @ 0x02216a00, 0x70 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02216aa8(void *, int, int, int *);
extern void func_ov003_02216a90(void *, int, int, int, unsigned char, unsigned char);
extern void func_020109a0(void *, int b, int c, unsigned short d);
extern unsigned int *func_0200f27c(void *, int);

void func_ov003_02216a00(void *self, void *data, int previous)
{
    unsigned char *p = (unsigned char *) data + 0xc;
    int b2 = p[2];
    int b3 = p[3];
    int b0 = p[0];
    int b1 = p[1];
    int loc[2];

    loc[0] = b0;
    loc[1] = b1;
    func_ov003_02216aa8((char *) self + 0x7d4, b2, b3, loc);
    func_ov003_02216a90((char *) self + 0x8f0, b2, b3, ((unsigned char *) self)[0x16c], (unsigned char) b0,
                        (unsigned char) b1);
    func_020109a0(self, 0x45, 3, 0);
    if (b3 != 0) {
        func_0200f27c(self, 0x1c);
    }
}
