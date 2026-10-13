/* func_ov121_0229a450 @ 0x0229a450, 0x30 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207cf8(void *);
extern void func_ov002_02207cf0(void *);

void func_ov121_0229a450(void *self)
{
    unsigned char v;
    void *p;

    v = *(unsigned char *) ((char *) self + 0xb1);
    if (v <= 7) {
        *(unsigned char *) ((char *) self + 0xad) = v;
        p = (char *) self + 0x2d8;
        func_ov002_02207cf8(p);
    } else {
        p = (char *) self + 0x2d8;
        func_ov002_02207cf0(p);
    }
}
