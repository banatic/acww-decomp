/* func_0204b6e0 @ 0x0204b6e0, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b42c(unsigned short *);

int func_0204b6e0(unsigned short *argument0)
{
    int flag = 0;
    int r = func_0204b42c((unsigned short *) argument0);
    switch (r) {
        case 0x2b:
        case 0x62:
        case 0xd0:
        case 0xff:
            flag = 1;
            break;
        default:
            break;
    }
    return flag;
}
