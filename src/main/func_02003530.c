/* func_02003530 @ 0x02003530, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202f144(int, int);

void func_02003530(void *arg0, int argument1)
{
    unsigned int *ptr;
    unsigned int val;

    func_0202f144((int) arg0, (int) argument1);
    ptr = (unsigned int *) ((char *) arg0 + 0xb0);
    val = *ptr;
    val |= 4;
    *ptr = val;
}
