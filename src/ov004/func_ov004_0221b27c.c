/* func_ov004_0221b27c @ 0x0221b27c, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_0225797c[];

int func_ov004_0221b27c(int index)
{
    if (index >= 0 && (unsigned) index < 0x20) {
        return data_ov004_0225797c[index];
    }
    return 0;
}
