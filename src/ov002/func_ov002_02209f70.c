/* func_ov002_02209f70 @ 0x02209f70, 0x2c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e4bc(void *self);
extern int func_0208a1cc(void *p);

int func_ov002_02209f70(char *self)
{
    int t = func_0208e4bc(self);

    if (t == 6 || t == 0xc) {
        self += 0xc;
        if (func_0208a1cc(self) == 2) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 1;
    }
}
