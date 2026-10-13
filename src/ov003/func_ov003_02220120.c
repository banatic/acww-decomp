/* func_ov003_02220120 @ 0x02220120, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov003_0223cef0[];

void func_ov003_02220120(void)
{
    unsigned int i;
    unsigned int *p;

    i = 0;
    do {
        p = &data_ov003_0223cef0[i];
        *p = 0;
        i++;
    } while (i < 0x20);
}
