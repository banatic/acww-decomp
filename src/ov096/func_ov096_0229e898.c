/* func_ov096_0229e898 @ 0x0229e898, 0x48 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov096_0229f47c(unsigned char *s, int x, unsigned char *ptr);
extern void func_ov096_0229f5e0(unsigned char *s, int x, unsigned short value, unsigned char byte);
extern void func_ov096_0229e6a0(unsigned char *s);

void func_ov096_0229e898(unsigned char *s, int x, int flag)
{
    switch (s[0xb1]) {
        case 1:
            func_ov096_0229f47c(s, x, s + 0x2e28);
            break;
        case 2:
            func_ov096_0229f5e0(s, x, *(unsigned short *) (s + 0xac), s[0xb0]);
            break;
    }
    if (flag) {
        func_ov096_0229e6a0(s);
    }
}
