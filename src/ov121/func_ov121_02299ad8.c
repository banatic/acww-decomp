/* func_ov121_02299ad8 @ 0x02299ad8, 0x48 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_02095b9c(unsigned short *);
extern int func_02095b84(unsigned short *);
extern int func_02095b1c(unsigned short *);

int func_ov121_02299ad8(int unused, int sel, int val)
{
    unsigned short v = (unsigned short) val;
    switch (sel) {
        case 0:
            if (func_02095b9c(&v)) {
                return 1;
            }
            break;
        case 1:
            if (func_02095b84(&v)) {
                return 1;
            }
            break;
        case 2:
            if (func_02095b1c(&v)) {
                return 1;
            }
            break;
        default:
            break;
    }
    return 0;
}
