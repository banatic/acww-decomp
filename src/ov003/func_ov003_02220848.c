/* func_ov003_02220848 @ 0x02220848, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *p);
extern void func_020edf54(void *p);
extern int data_ov003_02239b2c;
extern int data_020da13c;

void *func_ov003_02220848(void *p)
{
    *(volatile unsigned int *) p = (unsigned int) &data_ov003_02239b2c;
    *(volatile unsigned int *) p = (unsigned int) &data_020da13c;
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}
