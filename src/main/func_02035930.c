/* func_02035930 @ 0x02035930, 0xce bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020b5e10(void);
extern int func_020b5e84(unsigned char *);
extern void func_0200423c(int);

void func_02035930(void)
{
    int a, b;
    int a22, a25, a29;
    int b20, b22, b23, b25, b27, b29;
    int result;

    a = func_020b65c4();
    b = func_020b5e84((unsigned char *) func_020b5e10());

    a22 = (a == 0x22);
    a25 = (a == 0x25);
    a29 = (a == 0x29);

    b20 = (b == 0x20);
    b22 = (b == 0x22);
    b23 = (b == 0x23);
    b25 = (b == 0x25);
    b27 = (b == 0x27);
    b29 = (b == 0x29);

    result = 0;
    if (a == 0x20 && (b22 || b23 || b25 || b27 || b29)) {
        result = 1;
    } else if (a29 && b20) {
        result = 2;
    } else if (a25 && b20) {
        result = 3;
    } else if (a22 && b20) {
        result = 4;
    }
    if (result) {
        func_0200423c(result);
    }
}
