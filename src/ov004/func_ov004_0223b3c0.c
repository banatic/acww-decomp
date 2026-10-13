/* func_ov004_0223b3c0 @ 0x0223b3c0, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02213f8c(void *);
extern int func_ov004_02212564(void *);

int func_ov004_0223b3c0(char *self)
{
    if (self != 0) {
        switch (*(int *) (self + 0x780)) {
            case 0x1b:
                if (self != 0) {
                    return func_ov004_02213f8c(self);
                }
                break;
            case 0x27:
                if (self != 0) {
                    return func_ov004_02212564(self);
                }
                break;
        }
    }
    return 0;
}
