/* func_ov003_022208cc @ 0x022208cc, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223a248;
extern void func_02031e84(void *);
extern void func_020edb3c(void *);

void *func_ov003_022208cc(void *arg)
{
    *(void **) arg = &data_ov003_0223a248;
    func_02031e84(arg);
    func_020edb3c(arg);
    return arg;
}
