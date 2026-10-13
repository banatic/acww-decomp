/* func_02035750 @ 0x02035750, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern void func_0200423c(int);

void func_02035750(void)
{
    int status;
    int b23;
    int b22;
    int b24;
    int b25;
    int b26;
    int b27;
    int b28;
    int b29;
    int code;

    status = func_020b65c4();
    b22 = (status == 0x22);
    b23 = (status == 0x23);
    b24 = (status == 0x24);
    b25 = (status == 0x25);
    b26 = (status == 0x26);
    b27 = (status == 0x27);
    b28 = (status == 0x28);
    b29 = (status == 0x29);
    code = 0;

    if (status == 0x20) {
        code = 6;
    } else if (b23 || b24 || b27 || b28) {
        code = 0xb;
    } else if (b29) {
        code = 0xc;
    } else if (b25 || b26) {
        code = 0xd;
    } else if (b22) {
        code = 0xe;
    }

    if (code != 0) {
        func_0200423c(code);
    }
}
