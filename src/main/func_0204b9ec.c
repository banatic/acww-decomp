/* func_0204b9ec @ 0x0204b9ec, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b42c(void);

int func_0204b9ec(void)
{
    int ret = 0;
    int x = func_0204b42c();
    switch (x) {
        case 0x28:
        case 0x31:
        case 0x39:
        case 0x41:
        case 0x49:
        case 0x51:
        case 0x59:
        case 0x5f:
        case 0xca:
            ret = 1;
            break;
        default:
            break;
    }
    return ret;
}
