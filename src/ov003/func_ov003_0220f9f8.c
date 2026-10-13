/* func_ov003_0220f9f8 @ 0x0220f9f8, 0x64 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0220fae4(char *p, unsigned int *out1, unsigned int *out2, unsigned char *out3);
extern void func_ov003_0220fb30(char *self, unsigned int out1, unsigned int out2, int flag1, int flag2, int six, int val);

void func_ov003_0220f9f8(char *self, int val)
{
    unsigned char b;
    unsigned int out1, out2;
    if (*(int *) (self + 0x7f0) == 0x68) {
        *(unsigned short *) (self + 0xc84) = val;
    } else {
        int flag1, flag2;
        func_ov003_0220fae4(self + 0x8f0, &out1, &out2, &b);
        flag1 = (b != 0);
        flag2 = (b >> 4) != 0;
        func_ov003_0220fb30(self, out1, out2, flag1, flag2, 6, val);
    }
}
