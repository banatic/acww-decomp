/* func_ov145_0229a884 @ 0x0229a884, 0x64 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov145_0229a034(void *);
extern void func_ov145_0229a010(void *);
extern void func_ov145_02299fec(void *);
extern void func_ov145_02299fc8(void *);
extern void func_ov002_0220a580(void *);

void func_ov145_0229a884(void *self)
{
    unsigned short *p1;
    unsigned char *p2;
    int i;
    int val;

    p1 = (unsigned short *) ((char *) self + 0xb4);
    *p1 = 0;
    p2 = (unsigned char *) ((char *) self + 0xc0);
    *p2 = 0;

    for (i = 0; i < 9; i++) {
        ((unsigned short *) ((char *) self + 0xcb4))[i] = 0xfff1;
    }

    ((unsigned char *) self)[0xc5] = 3;
    ((unsigned char *) self)[0xc6] = 0;

    func_ov145_0229a034(self);
    func_ov145_0229a010(self);
    func_ov145_02299fec(self);
    func_ov145_02299fc8(self);

    func_ov002_0220a580((char *) self + 0x12c);
}
