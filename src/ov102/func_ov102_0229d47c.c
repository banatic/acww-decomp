/* func_ov102_0229d47c @ 0x0229d47c, 0x30 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_ov102_0229d258(void);

unsigned char func_ov102_0229d47c(void)
{
    unsigned short *ptr = func_ov102_0229d258();
    int i = 0;
    while (i < 15) {
        if (ptr[i] == 0xfff1) {
            return (unsigned char) (i + 15);
        }
        i++;
    }
    return 0x25;
}
