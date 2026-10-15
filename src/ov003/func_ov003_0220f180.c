/* func_ov003_0220f180 @ 0x0220f180, 0xc4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200fbe0(void *argument0);
extern void func_020109a0(void *, int b, int c, unsigned short d);
extern void func_0205eae0(void *, int, int, int);
extern int func_020912d4(int, void *, int, int);
extern int func_0203e420(void);
extern void RtcSendPxiCommand(int);
extern int func_0200f328(void *, int);
extern void func_02035684(int, int, int);

void func_ov003_0220f180(char *self, unsigned char *other, int previous)
{
    int ret;
    unsigned char b;
    char *p;

    b = other[0xc];
    ret = func_0200fbe0(self);

    if (ret == 3 || ret == 4 || ret == 10) {
        func_020109a0(self, 0x69, 3, 6);
        if (ret == 3) {
            func_0205eae0(self + 0x5a0, 0x14, 3, 1);
        } else if (ret == 4) {
            func_0205eae0(self + 0x5a0, 2, 9, 1);
        }
    } else {
        func_020109a0(self, 0x68, 3, 6);
    }

    func_0203e420();

    p = self + 0x7d4;
    *(int *) p = func_020912d4(0x34, self + 0x6e0, 0, 0);
    p[4] = b;

    if (b >= 2) {
        RtcSendPxiCommand(0x51);
        if (b == 2) {
            func_0200f328(self, 0x839);
        } else {
            func_0200f328(self, 0x838);
        }
        func_02035684(0xc, 0, 0);
    }

    func_0200f328(self, 0x816);
}
