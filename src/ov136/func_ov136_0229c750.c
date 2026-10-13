/* func_ov136_0229c750 @ 0x0229c750, 0x44 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov136_0229c574(void *a, int b);
extern void *func_ov134_022999ac(void *a);
extern void *func_ov002_0220a72c(void *a, int b);
extern void *data_ov136_0229d434[];

void *func_ov136_0229c750(void *a)
{
    if (func_ov136_0229c574(a, 2) != 0) {
        return func_ov134_022999ac((char *) a + 0x2c4);
    } else {
        unsigned char b = *(unsigned char *) ((char *) a + 0x2b77);
        if (b == 2) {
            char *p = (char *) a + 0xf8;
            return func_ov002_0220a72c(p, 6);
        } else {
            return data_ov136_0229d434[b];
        }
    }
}
