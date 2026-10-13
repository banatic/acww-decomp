/* func_ov004_02243c04 @ 0x02243c04, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02244be0(void *, int);

void func_ov004_02243c04(char *self)
{
    switch (*(signed char *) (self + 0x196)) {
        case 0x1b:
        case 0x1c:
        case 0x1d:
            if (*(short *) (self + 0x9c) < 5) {
                func_ov004_02244be0(self, 0);
            }
            break;
    }
}
