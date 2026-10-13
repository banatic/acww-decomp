/* func_ov144_0229ae24 @ 0x0229ae24, 0x40 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov144_0229a328(void *);
extern void func_ov144_0229a29c(void *);
extern void func_ov002_0220a580(void *);

void func_ov144_0229ae24(void *self)
{
    unsigned short *p;
    int i;
    unsigned short *q;

    p = (unsigned short *) ((char *) self + 0xb4);
    *p = 0;
    for (i = 0; i < 9; i++) {
        q = (unsigned short *) ((char *) self + 0x8f8 + i * 2);
        *q = 0xfff1;
    }
    func_ov144_0229a328(self);
    func_ov144_0229a29c(self);
    func_ov002_0220a580((char *) self + 0x128);
}
