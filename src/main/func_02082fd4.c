/* func_02082fd4 @ 0x02082fd4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083100(void *);
extern int data_020e1a04;

void *func_02082fd4(void *p)
{
    func_02083100(p);
    *(int *) p = (int) &data_020e1a04;
    return p;
}
