/* func_ov004_0223fa80 @ 0x0223fa80, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov004_02259a34[];

int func_ov004_0223fa80(void)
{
    unsigned char i;
    char *p = data_ov004_02259a34;
    for (i = 0; i < 0x20; i++) {
        if (*(int *) (p + 0x198) == 0) {
            return i;
        }
        p += 0x2d8;
    }
    return -1;
}
