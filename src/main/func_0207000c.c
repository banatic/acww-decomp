/* func_0207000c @ 0x0207000c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020df328[2];
extern int data_021cfca0;
extern int func_0206ffbc(int);

int func_0207000c(int param)
{
    if (data_020df328[0] != 1) {
        return 0;
    }
    if (data_021cfca0 == 0) {
        return 0;
    }
    if (func_0206ffbc(param) != 0) {
        return 0;
    }
    data_020df328[1] = param;
    data_020df328[0] = 2;
    return 1;
}
