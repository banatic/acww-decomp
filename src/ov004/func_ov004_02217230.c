/* func_ov004_02217230 @ 0x02217230, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_022476a4[];
int func_ov004_02217230(unsigned char *self)
{
    unsigned int i;
    for (i = 0; i < 3; i++) {
        if (*(int *) (self + 0x780) == data_ov004_022476a4[i]) {
            return i;
        }
    }
    return -1;
}
