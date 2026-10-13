/* func_ov142_0229967c @ 0x0229967c, 0x74 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov142_0229ab80(void *self, int val);
extern void func_ov142_022996f0(void *self, int val);

void func_ov142_0229967c(char *self)
{
    unsigned char state = *(unsigned char *) (self + 0xc2);

    switch (state) {
        case 0:
            return;
        case 1:
            if (*(unsigned char *) (self + 0xc1) != 0) {
                *(unsigned char *) (self + 0xc1) = *(volatile unsigned char *) (self + 0xc1) - 1;
            } else {
                *(unsigned char *) (self + 0xc2) = 2;
                func_ov142_0229ab80(self, *(unsigned char *) (self + 0xbd));
            }
            break;
        case 2:
            if (*(unsigned char *) (self + 0xc1) < 3) {
                *(unsigned char *) (self + 0xc1) = *(volatile unsigned char *) (self + 0xc1) + 1;
            } else {
                *(unsigned char *) (self + 0xc2) = 0;
                return;
            }
            break;
        default:
            break;
    }

    func_ov142_022996f0(self, *(unsigned char *) (self + 0xc1));
}
