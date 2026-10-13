/* func_ov125_022a0358 @ 0x022a0358, 0xc0 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020e9958(void *, int);
extern void func_020e993c(void *, void *);
extern void *func_020984e8(void);
extern void *func_020996b8(void *);
extern void *func_02072bb0(void *, int);
extern void *func_02072da0(void *);
extern void *func_02072d4c(void *);
extern void *func_02072f88(void *);
extern void func_020025c4(void *, void *, int, int, int);
extern void func_02002a88(void *, int, int, int, int);
extern void func_02002bd0(void *, int, int, int, int);
extern void MIi_CpuCopy16(const void *, void *, unsigned int);
extern void *data_021fbe94;

void func_ov125_022a0358(void)
{
    void *dev;
    void *buf;
    void *buf2;
    void *h;
    unsigned char i;
    int off;

    dev = data_021fbe94;
    buf = func_020e9958(dev, 0x1000);
    h = func_020996b8(func_020984e8());
    for (i = 0; i < 8; i++) {
        func_020025c4(func_02072da0(func_02072bb0(h, i)), buf, i * 4, 4, 4);
    }
    func_02002a88(buf, 8, 0xc0, 0xc0, 0x13f);
    func_020e993c(dev, buf);

    buf2 = func_020e9958(dev, 0x100);
    off = 0;
    for (i = 0; i < 8; i++) {
        MIi_CpuCopy16(func_02072f88(func_02072d4c(func_02072bb0(h, i))), (unsigned short *) buf2 + off, 0x20);
        off += 0x10;
    }
    func_02002bd0(buf2, 8, 5, 5, 0xc);
    func_020e993c(dev, buf2);
}
