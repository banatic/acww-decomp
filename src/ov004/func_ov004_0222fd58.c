/* func_ov004_0222fd58 @ 0x0222fd58, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char *data_ov004_02258558;
void func_ov004_0222fd58(int v)
{
    char *p = data_ov004_02258558;
    if (p != 0) {
        *(int *) (p + 0x334) = v << 12;
    }
}
