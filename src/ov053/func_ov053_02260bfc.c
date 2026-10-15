/* func_ov053_02260bfc @ 0x02260bfc, 0x18 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov053_02261b08;
extern void *func_0202eb20(void *);

void *func_ov053_02260bfc(void *p)
{
    *(int *) p = (int) &data_ov053_02261b08;
    func_0202eb20(p);
    return p;
}
