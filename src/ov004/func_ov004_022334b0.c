/* func_ov004_022334b0 @ 0x022334b0, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *ptr);
extern int data_ov004_02255b7c;
extern int data_020da13c;

void *func_ov004_022334b0(void *p)
{
    volatile int *vp;
    vp = (volatile int *) p;
    *vp = (int) &data_ov004_02255b7c;
    *vp = (int) &data_020da13c;
    func_020ee62c(p);
    return p;
}
