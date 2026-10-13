/* func_02047114 @ 0x02047114, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern int data_020cac9c[];

int func_02047114(void)
{
    unsigned short r4 = 0x1554;
    int r0 = func_020644cc(100);
    int *p = data_020cac9c;
    int i = 0;

    while (i < 9) {
        r0 -= *p;
        if (r0 < 0) {
            break;
        }
        r4 = (unsigned short) (r4 + 1);
        p++;
        i++;
    }
    return r4;
}
