/* func_ov004_0222fd94 @ 0x0222fd94, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef int (*Fn)(void *self, int k);
extern void *data_ov004_02258558;

int func_ov004_0222fd94(void)
{
    void *p = data_ov004_02258558;
    if (p != 0) {
        return (*(Fn **) p)[24](p, 3);
    }
    return 0;
}
