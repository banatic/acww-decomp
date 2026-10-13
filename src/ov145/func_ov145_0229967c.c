/* func_ov145_0229967c @ 0x0229967c, 0x74 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov145_0229996c(void *self, int val);
extern void func_ov145_022996f0(void *self, int val);

void func_ov145_0229967c(char *self)
{
    unsigned char state = *(unsigned char *) (self + 0xc6);

    switch (state) {
        case 0:
            return;
        case 1:
            if (*(unsigned char *) (self + 0xc5) != 0) {
                *(unsigned char *) (self + 0xc5) = *(volatile unsigned char *) (self + 0xc5) - 1;
            } else {
                *(unsigned char *) (self + 0xc6) = 2;
                func_ov145_0229996c(self, *(unsigned char *) (self + 0xc1));
            }
            break;
        case 2:
            if (*(unsigned char *) (self + 0xc5) < 3) {
                *(unsigned char *) (self + 0xc5) = *(volatile unsigned char *) (self + 0xc5) + 1;
            } else {
                *(unsigned char *) (self + 0xc6) = 0;
                return;
            }
            break;
        default:
            break;
    }

    func_ov145_022996f0(self, *(unsigned char *) (self + 0xc5));
}
