/* func_02065268 @ 0x02065268, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021cd864;

void func_02065268(int val)
{
    unsigned int base = data_021cd864;
    if (base != 0) {
        int *p = (int *) (base + 0x124);
        *p = val;
        p[5] = 1;
    }
}
