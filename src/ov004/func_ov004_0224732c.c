/* func_ov004_0224732c @ 0x0224732c, 0x3a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);

int func_ov004_0224732c(void)
{
    int r = 0;
    switch (func_020b65c4()) {
        case 0x1a:
            r = 0;
            break;
        case 0x1b:
            r = 1;
            break;
        case 0x1c:
            r = 2;
            break;
        case 0x1d:
        case 0x1e:
            r = 3;
            break;
    }
    return r;
}
