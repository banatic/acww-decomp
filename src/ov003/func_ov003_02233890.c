/* func_ov003_02233890 @ 0x02233890, 0xa0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_02270e80(void *a, void *b);
extern int func_020e8870(short *a, int b, int c);
extern void func_ov003_022353a4(void *a, int b, int c);
extern void func_ov003_02230e18(void *a, void *b);

void func_ov003_02233890(char *self)
{
    short *p = (short *) (self + 0x242);
    switch (*(unsigned char *) (self + 0x251)) {
        case 0:
            func_ov068_02270e80(self, p);
            break;
        case 0xf: {
            short h = *(short *) (self + 0x23a);
            if (func_020e8870(&h, *(short *) (self + 0x240), 0x5b0)) {
                *(char *) (self + 0x251) = 0;
            }
            func_ov003_022353a4(self, 0, 1);
            *(short *) (self + 0x23a) = h;
            break;
        }
        case 9:
        case 0xb:
            func_ov003_02230e18(self, p);
            *p = (short) (*p + 1);
            break;
        case 0x13:
            *(char *) (self + 0x251) = 0;
            break;
    }
}
