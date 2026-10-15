/* func_ov109_0229cb9c @ 0x0229cb9c, 0x38 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov109_0229ccb4(int arg0, unsigned int arg1);
extern int func_ov109_0229cc98(int a, int b);
extern int func_ov094_0229ab90(int a, int b);

int func_ov109_0229cb9c(int p1, int p2)
{
    if (func_ov109_0229ccb4(p1, p2)) {
        return func_ov094_0229ab90(p1 + 0xcc, func_ov109_0229cc98(p1, p2)) - 0x10;
    }
    if (p2 == 0xf) {
        return 0xb6;
    }
    return 0;
}
