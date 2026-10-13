/* func_ov004_02215718 @ 0x02215718, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022110e4(void *);
extern char data_ov004_02250c04;
extern char data_ov004_02250cb0;

void *func_ov004_02215718(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02250c04;
    *(void **) ((char *) this + 0xec) = &data_ov004_02250cb0;
    return this;
}
