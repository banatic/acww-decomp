/* func_ov101_0229d624 @ 0x0229d624, 0x98 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208e28(unsigned char *);
extern int func_ov002_02208054(unsigned char *, int);
extern void func_ov101_0229c51c(unsigned char *);
extern int func_ov002_02208b00(unsigned char *, unsigned char, unsigned char);
extern void func_ov002_02209114(unsigned char *, int, int);
extern unsigned char *func_ov002_02208098(unsigned char *, unsigned char value);

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov101_0229d624(unsigned char *p)
{
    int flag;
    int result;
    unsigned char *q;

    if (func_ov002_02208e28(p + 0x2300) == 0) {
        return;
    }
    if (func_ov002_02208054(p, 1) != 0) {
        func_ov101_0229c51c(p);
        return;
    }
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (flag != 0) {
        result = func_ov002_02208b00(p + 0x2300, data_021f6c58, data_021f6c54);
        if (result < 0) {
            return;
        }
        func_ov002_02209114(p + 0x2300, result, 1);
        q = p + result;
        p[0xb7] = q[0x26ed];
        func_ov002_02208098(p, 0x14);
    }
}
