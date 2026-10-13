/* func_ov004_02244620 @ 0x02244620, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0224457c(void *);
extern void func_ov004_02244c40(void *);

void func_ov004_02244620(char *self)
{
    switch (*(short *) (self + 0x172)) {
        case 0:
            func_ov004_0224457c(self);
            break;
        case 6:
            func_ov004_02244c40(self);
            break;
        default:
            *(char *) (self + 0x9a) = 0;
            *(short *) (self + 0x172) = 0;
            *(short *) (self + 0x9c) = 0;
            break;
    }
}
