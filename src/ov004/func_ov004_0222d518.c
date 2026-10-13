/* func_ov004_0222d518 @ 0x0222d518, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef int (*Fn)(void *self, int k);
extern void *data_ov004_0225827c;

int func_ov004_0222d518(void)
{
    void *p = data_ov004_0225827c;
    if (p != 0) {
        return (*(Fn **) p)[24](p, 1);
    }
    return 0;
}
