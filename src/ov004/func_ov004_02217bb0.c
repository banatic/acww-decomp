/* func_ov004_02217bb0 @ 0x02217bb0, 0x26 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(char *self, int b);
extern int func_02053990(char *self);
int func_ov004_02217bb0(char *self, int b)
{
    int r;
    if (b == 0 && func_0204bcdc(self, b) != 0 && func_02053990(self) == 5) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}
