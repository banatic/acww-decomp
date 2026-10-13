/* func_ov068_022746fc @ 0x022746fc, 0x18 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb20(void *);
extern int data_ov068_02277dc0;

void *func_ov068_022746fc(void *this)
{
    *(int **) this = &data_ov068_02277dc0;
    func_0202eb20(this);
    return this;
}
