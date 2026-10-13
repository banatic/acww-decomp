/* func_ov141_0229a174 @ 0x0229a174, 0x10c bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern void func_02074308(unsigned char *);
extern int func_020ec148(void);
extern void func_020730c8(void);
extern int *func_020eb92c(void);
extern int func_020eb998(int);
extern int func_020eb9c4(int);
extern void MI_CpuCopy8(int, unsigned char *, int);
extern int func_ov141_0229a028(unsigned char *, int);
extern int func_ov141_0229a004(unsigned char *);
extern void func_ov141_02299fd0(unsigned char *, int, int);
extern void func_ov139_022997c0(unsigned char *, int, unsigned char *);
extern void func_ov141_0229a0dc(unsigned char *);

void func_ov141_0229a174(unsigned char *self)
{
    int i;
    int a;
    int *array;
    int val, val2, val3, val4;
    int r7, ret, ext, ext2;
    unsigned char buffer[0x19];
    unsigned char r4;
    int item;
    unsigned char *ptr;

    func_02074308(self);
    a = func_020ec148();

    for (i = 0; i < 6; i++) {
        if ((self + i)[0x1a7f] == 1) {
            (self + i)[0x1a7f] = 2;
        }
    }

    func_020730c8();
    array = func_020eb92c();

    val2 = 0;
    val3 = 0;
    val4 = 0;
    r4 = 0;

    while (r4 < a) {
        item = array[r4];
        if (item != 0) {
            func_020730c8();
            r7 = func_020eb998(item);
            if (r7 == 0x1a) {
                func_020730c8();
                ext = func_020eb9c4(item);
                MI_CpuCopy8(ext, buffer, r7);
                if (buffer[0x18] == 0) {
                    ret = func_ov141_0229a028(self, item);
                    if (ret == ~val3) {
                        r7 = func_ov141_0229a004(self);
                        if (r7 != ~val4) {
                            func_ov141_02299fd0(self, r7, item);
                            func_020730c8();
                            val = func_020eb998(item);
                            func_020730c8();
                            ext2 = func_020eb9c4(item);
                            ptr = (self + 0x11cc) + r7 * 0x1a;
                            MI_CpuCopy8(ext2, ptr, val);
                            func_ov139_022997c0(self + 0x94, r7, ptr);
                            (self + r7)[0x1a85] = val2;
                        }
                    } else {
                        func_ov141_02299fd0(self, ret, item);
                    }
                }
            }
        }
        r4 = (unsigned char) (r4 + 1);
    }

    func_ov141_0229a0dc(self);
}
