/* field_actor_67: 2 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02216a00 @ 0x02216a00, 0x70 bytes, Thumb
 * func_ov003_022169a4 @ 0x022169a4, 0x5c bytes, Thumb
 */

extern void func_ov003_02216aa8(void *, int, int, int *);
extern void func_ov003_02216a90(void *, int, int, int, unsigned char, unsigned char);
extern void func_020109a0(void *, int b, int c, unsigned short d);
extern unsigned int *func_0200f27c(void *, int);
extern void func_ov003_02216a70(void *base, unsigned char *a, unsigned char *b, unsigned char *c, unsigned char *d,
                                unsigned char *e);
extern int func_ov003_02216ab8(void *obj, unsigned char a, int b, void *c, int d, int e);

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

void func_ov003_022169a4(void *obj, int param)
{
    unsigned char buf[5];
    unsigned int vals[2];

    func_ov003_02216a70((char *) obj + 0x8f0, buf, buf + 1, buf + 2, buf + 3, buf + 4);

    *((unsigned char *) ((char *) obj + 0x16c)) = buf[2];

    if (buf[1] == 0) {
        vals[0] = buf[3];
        vals[1] = buf[4];
        func_ov003_02216ab8(obj, buf[0], 0, vals, 6, param);
    }
}
