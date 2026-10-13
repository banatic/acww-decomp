/* func_0204b8d4 @ 0x0204b8d4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b42c(int);

int func_0204b8d4(int arg)
{
    int ret = 0;
    int x = func_0204b42c(arg);
    switch (x) {
        case 54:
        case 62:
        case 70:
        case 78:
        case 86:
        case 207:
            ret = 1;
            break;
    }
    return ret;
}
