/* func_ov073_02278e9c @ 0x02278e9c, 0x18 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov073_02279a70;
extern void func_0202eb20(void *);

void *func_ov073_02278e9c(void *p)
{
    *((void **) p) = (void *) &data_ov073_02279a70;
    func_0202eb20(p);
    return p;
}
