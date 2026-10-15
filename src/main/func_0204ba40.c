/* func_0204ba40 @ 0x0204ba40, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b42c(unsigned short *);

int func_0204ba40(unsigned short *argument0)
{
    int v;
    int result = 0;

    v = func_0204b42c((unsigned short *) argument0);
    switch (v) {
        case 0x27:
        case 0x30:
        case 0x38:
        case 0x40:
        case 0x48:
        case 0x50:
        case 0x58:
        case 0x5e:
        case 0xc9:
            result = 1;
            break;
        default:
            break;
    }
    return result;
}
