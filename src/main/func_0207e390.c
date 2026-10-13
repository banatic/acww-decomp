/* func_0207e390 @ 0x0207e390, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_020996e0(void);
extern int func_0207e2a4(int a, int b, int c);
extern int func_0207e25c(int a, int b, int c);
extern int func_0207e214(int a, int b, int c);

int func_0207e390(int a, int b, int c)
{
    int result = 0;
    int flag;
    unsigned short value;
    unsigned short *ptr;

    ptr = func_020996e0();
    flag = 0;
    value = *ptr;
    if (value >= 0x1431u && value <= 0x1470u) {
        flag = 1;
    }

    if (flag) {
        if (func_0207e2a4(a, b, c) != 0 || func_0207e25c(a, b, c) != 0 || func_0207e214(a, b, c) != 0) {
            result = 1;
        }
    }

    return result;
}
