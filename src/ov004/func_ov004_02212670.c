/* func_ov004_02212670 @ 0x02212670, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022110e4(void *);
extern char data_ov004_02250ad8;
extern char data_ov004_02250b84;

void *func_ov004_02212670(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02250ad8;
    *(void **) ((char *) this + 0xec) = &data_ov004_02250b84;
    return this;
}
