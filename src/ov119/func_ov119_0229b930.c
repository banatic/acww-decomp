/* func_ov119_0229b930 @ 0x0229b930, 0x74 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a314(void *);
extern void func_ov002_0220a254(void *);
extern void func_ov002_0220a2b4(void *);
extern int func_ov119_0229ba00(void *);
extern int func_ov119_0229b9c8(void *);
extern void func_ov002_0220a05c(void *, int, int, int, int);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);

void func_ov119_0229b930(void *self)
{
    int r4;
    int r2;
    unsigned char b;
    unsigned char v = *(unsigned char *) ((char *) self + 0xa0);

    if (v <= 7) {
        func_ov002_0220a314((char *) self + 0xda8);
    } else if (v >= 0xe && v <= 0x15) {
        func_ov002_0220a254((char *) self + 0xda8);
    } else {
        func_ov002_0220a2b4((char *) self + 0xda8);
    }

    r4 = func_ov119_0229ba00(self);
    r2 = func_ov119_0229b9c8(self);
    func_ov002_0220a05c((char *) self + 0xda8, r4, r2, 3, 1);

    b = *(unsigned char *) ((char *) self + 0x8d);
    *(unsigned char *) ((char *) self + 0x9f) = b;

    func_ov002_02208098(self, 3);
}
