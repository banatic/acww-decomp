/* func_ov094_0229b794 @ 0x0229b794, 0xfc bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229b174(void *arg);
extern void func_ov094_0229b8d8(unsigned char *self, unsigned int idx);
extern unsigned int func_02065ec0(void);
extern void func_ov094_0229b77c(unsigned char *self, unsigned int idx);
extern void func_02002d14(void *data, void *ptr, int a, int b, int c, int d);
extern void *data_021fbe94;
extern char data_ov094_0229c154[];

void func_ov094_0229b794(unsigned char *self, unsigned int flags)
{
    unsigned int f2;
    unsigned char idx;
    unsigned int f3;
    unsigned int f0;
    unsigned int v;
    void *ptr;
    unsigned int f1;

    func_ov094_0229b174(self + 0x18);
    idx = 0;
    f0 = flags & 1;
    f3 = flags & 8;
    f1 = flags & 2;
    f2 = flags & 4;

    do {
        func_ov094_0229b8d8(self, idx);
        v = func_02065ec0();
        switch (v) {
            case 1:
                if (f0) {
                    func_ov094_0229b77c(self, idx);
                }
                break;
            case 4:
                if (f3 || f0) {
                    func_ov094_0229b77c(self, idx);
                }
                break;
            case 2:
            case 3:
            case 5:
            case 6:
                if (f1) {
                    func_ov094_0229b77c(self, idx);
                }
                break;
            case 7:
            case 8:
                if (f2) {
                    func_ov094_0229b77c(self, idx);
                }
                break;
            default:
                break;
        }
        idx = (unsigned char) (idx + 1);
    } while (idx <= 9);

    ptr = data_021fbe94;
    if (f0) {
        func_02002d14(data_ov094_0229c154, ptr, 8, 4, 4, 4);
    }
    if (f1) {
        func_02002d14(data_ov094_0229c154, ptr, 8, 4, 5, 5);
    }
    if (f2) {
        func_02002d14(data_ov094_0229c154, ptr, 8, 4, 6, 6);
    }
}