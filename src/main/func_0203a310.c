/* func_0203a310 @ 0x0203a310, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *ptr);
extern int data_020da5f8;
extern int data_020da6dc;

void *func_0203a310(void *p)
{
    volatile int *vp;
    vp = (volatile int *) p;
    *vp = (int) &data_020da5f8;
    *vp = (int) &data_020da6dc;
    func_020edb3c(p);
    return p;
}
