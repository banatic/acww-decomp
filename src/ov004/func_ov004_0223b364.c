/* func_ov004_0223b364 @ 0x0223b364, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02213f78(void *self);
extern int func_ov004_02212550(void *self);
int func_ov004_0223b364(unsigned char *self)
{
    if (self != 0) {
        switch (*(int *) (self + 0x780)) {
            case 0x1b:
                if (self != 0) {
                    return func_ov004_02213f78(self);
                }
                break;
            case 0x27:
                if (self != 0) {
                    return func_ov004_02212550(self);
                }
                break;
        }
    }
    return 0;
}
