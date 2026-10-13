/* func_ov138_0229c7a8 @ 0x0229c7a8, 0x54 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov138_0229c574(void *self, int n);
extern int func_ov134_022999e0(void *ptr);
extern int func_ov002_0220a768(void *ptr, int n);
extern int data_ov138_0229d404[];

int func_ov138_0229c7a8(void *self)
{
    if (func_ov138_0229c574(self, 2)) {
        return func_ov134_022999e0((char *) self + 0x2c8);
    } else {
        unsigned char b = *((unsigned char *) self + 0x95);
        switch (b) {
            case 3:
                return func_ov002_0220a768((char *) self + 0xfc, 6);
            case 4:
                return func_ov002_0220a768((char *) self + 0xfc, 7);
            default:
                return data_ov138_0229d404[b];
        }
    }
}
