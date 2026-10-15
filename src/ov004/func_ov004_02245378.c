/* func_ov004_02245378 @ 0x02245378, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02256780;
extern void *func_ov004_02245474(void *);

void *func_ov004_02245378(void *arg)
{
    *((void **) arg) = &data_ov004_02256780;
    func_ov004_02245474(arg);
    return arg;
}
