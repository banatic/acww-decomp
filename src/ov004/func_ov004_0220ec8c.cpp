/* func_ov004_0220ec8c @ 0x0220ec8c, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern "C" void *func_ov004_022320d8(void);
extern "C" unsigned char func_02062300(void *p);
extern "C" int func_02031914(int);

extern unsigned char data_020e54a8;

inline int chk(void)
{
    if (data_020e54a8 == 1) {
        return 1;
    }
    return 0;
}

extern "C" int func_ov004_0220ec8c(void)
{
    unsigned short v;
    int m;
    int r;
    void *p;

    if (chk() != 0) {
        p = func_ov004_022320d8();
        m = 0;
        v = *(unsigned short *) p;
        if (v >= 0x1144 && v <= 0x1187) {
            m = 1;
        }
        if (m != 0) {
            r = func_02031914((int) func_02062300(p));
            if (r != 0xffff) {
                return r;
            }
        }
        return 0x4c1;
    }
    return 0xffff;
}
