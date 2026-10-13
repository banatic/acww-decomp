/* func_0204b910 @ 0x0204b910, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b42c(void);

int func_0204b910(void)
{
    int result = 0;
    int x = func_0204b42c();

    switch (x) {
        case 0x2a:
        case 0x33:
        case 0x3b:
        case 0x43:
        case 0x4b:
        case 0x53:
        case 0x5b:
        case 0x61:
        case 0x66:
        case 0x67:
        case 0x68:
        case 0x69:
        case 0x6a:
        case 0x6b:
        case 0x6c:
        case 0x6d:
        case 0xcc:
            result = 1;
            break;
        default:
            break;
    }

    return result;
}
