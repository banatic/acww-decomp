/* func_02078d68 @ 0x02078d68, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02078d68(int *r0);

void func_02078d68(int *r0)
{
    int i;
    int *p;

    i = 0;
    do {
        p = &r0[i];
        *p = 0;
        i++;
    } while (i < 5);
}
