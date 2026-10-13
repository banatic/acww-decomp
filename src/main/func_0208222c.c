/* func_0208222c @ 0x0208222c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020cd4ac[];

int *func_0208222c(unsigned int r0)
{
    if (r0 >= 6) {
        r0 = 0;
    }
    return &data_020cd4ac[r0];
}
