/* func_02035864 @ 0x02035864, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65b8(void);
extern int func_020b65c4(void);
extern void func_0200422c(int);

void func_02035864(void)
{
    int a, b;
    int b20, b22, b23, b25, b27, b29;
    int c22, c25, c29;
    int result;

    a = func_020b65b8();
    b = func_020b65c4();

    b20 = (a == 0x20);
    b22 = (a == 0x22);
    b23 = (a == 0x23);
    b25 = (a == 0x25);
    b27 = (a == 0x27);
    b29 = (a == 0x29);

    c22 = (b == 0x22);
    c25 = (b == 0x25);
    c29 = (b == 0x29);

    result = 0;
    if (b == 0x20 && (b22 || b23 || b25 || b27 || b29)) {
        result = 1;
    } else if (c29 && b20) {
        result = 2;
    } else if (c25 && b20) {
        result = 3;
    } else if (c22 && b20) {
        result = 4;
    }
    if (result) {
        func_0200422c(result);
    }
}
