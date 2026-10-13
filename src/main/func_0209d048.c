/* func_0209d048 @ 0x0209d048, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1ac0[];

int func_0209d048(int val)
{
    int *p = (int *) data_020d1ac0;
    unsigned int i = 0;
    while (i < 6) {
        if (*p == val) {
            return 1;
        }
        p++;
        i++;
    }
    return 0;
}
