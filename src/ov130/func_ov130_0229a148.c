/* func_ov130_0229a148 @ 0x0229a148, 0x20 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *data_ov130_0229a90c[];

unsigned char *func_ov130_0229a148(unsigned char *obj)
{
    unsigned char idx = obj[5];
    unsigned char *ptr = data_ov130_0229a90c[idx];
    unsigned char mode = obj[8];
    if (mode == 0 || mode == 2) {
        if (idx <= 10) {
            ptr += 0x40;
        }
    }
    return ptr;
}
