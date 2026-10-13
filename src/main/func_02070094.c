/* func_02070094 @ 0x02070094, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020df328;
extern unsigned int data_021cfca0;

int func_02070094(void)
{
    if (data_020df328 != 1) {
        return 0;
    }
    if (data_021cfca0 != 0) {
        return 0;
    }
    return 1;
}
