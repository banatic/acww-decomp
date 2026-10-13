/* func_ov107_0229d908 @ 0x0229d908, 0x98 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208e28(unsigned char *);
extern int func_ov002_02208054(unsigned char *, int);
extern void func_ov107_0229cb78(unsigned char *);
extern int func_ov002_02208b00(unsigned char *, unsigned char, unsigned char);
extern void func_ov002_02209114(unsigned char *, int, int);
extern void func_ov002_02208098(unsigned char *, int);

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov107_0229d908(unsigned char *p)
{
    int flag;
    int result;
    unsigned char *q;

    if (func_ov002_02208e28(p + 0x2318) == 0) {
        return;
    }
    if (func_ov002_02208054(p, 1) != 0) {
        func_ov107_0229cb78(p);
        return;
    }
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (flag != 0) {
        result = func_ov002_02208b00(p + 0x2318, data_021f6c58, data_021f6c54);
        if (result < 0) {
            return;
        }
        func_ov002_02209114(p + 0x2318, result, 1);
        q = p + result;
        p[0xbc] = q[0x2705];
        func_ov002_02208098(p, 0xc);
    }
}
