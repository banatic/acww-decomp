/* func_ov004_0223ea04 @ 0x0223ea04, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *ptr);
extern int data_ov004_022561dc;
extern int data_020da13c;

void *func_ov004_0223ea04(void *p)
{
    volatile int *vp;
    vp = (volatile int *) p;
    *vp = (int) &data_ov004_022561dc;
    *vp = (int) &data_020da13c;
    func_020ee62c(p);
    return p;
}
