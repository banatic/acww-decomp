/* func_0204b678 @ 0x0204b678, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b42c(unsigned short *);

int func_0204b678(unsigned short *argument0)
{
    int result = 0;
    int v = func_0204b42c((unsigned short *) argument0);
    switch (v) {
        case 45:
        case 100:
        case 210:
        case 257:
            result = 1;
            break;
        default:
            break;
    }
    return result;
}
