/* func_0204b6ac @ 0x0204b6ac, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b42c(unsigned short *);

int func_0204b6ac(unsigned short *argument0)
{
    int r = 0;
    int v = func_0204b42c((unsigned short *) argument0);
    switch (v) {
        case 0x2c:
        case 0x63:
        case 0xd1:
        case 0x100:
            r = 1;
            break;
        default:
            break;
    }
    return r;
}
