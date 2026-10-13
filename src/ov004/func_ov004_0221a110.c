/* func_ov004_0221a110 @ 0x0221a110, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022110e4(void *);
extern char data_ov004_02252e00;
extern char data_ov004_02252eac;

void *func_ov004_0221a110(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02252e00;
    *(void **) ((char *) this + 0xec) = &data_ov004_02252eac;
    return this;
}
