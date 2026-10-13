/* func_ov138_0229c754 @ 0x0229c754, 0x54 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov138_0229c574(void *self, int n);
extern int func_ov134_022999ac(void *ptr);
extern int func_ov002_0220a72c(void *ptr, int n);
extern int data_ov138_0229d418[];

int func_ov138_0229c754(void *self)
{
    if (func_ov138_0229c574(self, 2)) {
        return func_ov134_022999ac((char *) self + 0x2c8);
    } else {
        unsigned char b = *((unsigned char *) self + 0x95);
        switch (b) {
            case 3:
                return func_ov002_0220a72c((char *) self + 0xfc, 6);
            case 4:
                return func_ov002_0220a72c((char *) self + 0xfc, 7);
            default:
                return data_ov138_0229d418[b];
        }
    }
}
