/* func_020b5650 @ 0x020b5650, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e5320;
extern int data_020e3c94;
extern int data_020da13c;
extern void func_020ee62c(void *p);

void *func_020b5650(void *p)
{
    volatile unsigned int *q = p;
    *q = (unsigned int) &data_020e5320;
    *q = (unsigned int) &data_020e3c94;
    *q = (unsigned int) &data_020da13c;
    func_020ee62c(p);
    return p;
}
