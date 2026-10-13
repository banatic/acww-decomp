/* func_ov002_02209f9c @ 0x02209f9c, 0x62 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e4bc(void *self);
extern int func_0208a1cc(void *p);

int func_ov002_02209f9c(char *self)
{
    switch (func_0208e4bc(self)) {
        case 4:
        case 10:
            self += 0xc;
            if (func_0208a1cc(self) >= 4) {
                return 1;
            } else {
                return 0;
            }
        case 5:
        case 11:
            self += 0xc;
            if (func_0208a1cc(self) < 3) {
                return 1;
            } else {
                return 0;
            }
        case 6:
        case 12:
            return 1;
    }
    return 0;
}
