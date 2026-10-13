/* func_ov004_022370f4 @ 0x022370f4, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02236464(void *self, void *buf);
extern void func_ov004_0223635c(void *self, void *buf);

void func_ov004_022370f4(void *self)
{
    char buf[0x10];
    unsigned char *p;

    if (func_ov004_02236464(self, buf) != 0) {
        if (*((unsigned char *) self + 0x255) != 0) {
            if (*((unsigned char *) self + 0x256) != 3) {
                *((unsigned char *) self + 0x256) = 2;
            }
        } else {
            func_ov004_0223635c(self, buf);
        }
    }
}
