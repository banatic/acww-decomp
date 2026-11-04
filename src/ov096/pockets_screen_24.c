/* pockets_screen_24: 3 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_0229e90c @ 0x0229e90c, 0x4e bytes, Thumb
 * func_ov096_0229e8e0 @ 0x0229e8e0, 0x2c bytes, Thumb
 * func_ov096_0229e898 @ 0x0229e898, 0x48 bytes, Thumb
 */

extern int func_ov096_0229f830(void *param0, int param1);
extern int func_ov096_0229f820(void *param0, int param1);
extern void func_ov096_0229e9a0(void *param0, int param1);
extern void func_ov096_0229e95c(void *param0, int param1);
extern void func_ov096_0229e0f8(void *param0, unsigned short param1);
extern void func_ov096_0229f47c(unsigned char *s, int x, unsigned char *ptr);
extern void func_ov096_0229f5e0(unsigned char *s, int x, unsigned short value, unsigned char byte);
extern void func_ov096_0229e6a0(unsigned char *s);

void func_ov096_0229e90c(void *param0, int param1)
{
    if (func_ov096_0229f830(param0, param1)) {
        func_ov096_0229e9a0(param0, param1);
    } else {
        if (func_ov096_0229f820(param0, param1)) {
            func_ov096_0229e95c(param0, param1);
        } else {
            if (param1 == 0x25) {
                func_ov096_0229e9a0(param0, param1);
                func_ov096_0229e0f8(param0, *(unsigned short *) ((char *) param0 + 0xac));
            }
        }
    }
}

void func_ov096_0229e8e0(int a, int b)
{
    if (func_ov096_0229f830((void *) a, b) || func_ov096_0229f820((void *) a, b)) {
        func_ov096_0229e9a0((void *) a, b);
    }
}

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
