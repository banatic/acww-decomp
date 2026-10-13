/* func_ov081_02279024 @ 0x02279024, 0x18 bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb20(void *);
extern int data_ov081_0227972c;

void *func_ov081_02279024(void *p)
{
    *(int *) p = (int) &data_ov081_0227972c;
    func_0202eb20(p);
    return p;
}
