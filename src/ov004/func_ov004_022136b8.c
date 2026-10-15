/* func_ov004_022136b8 @ 0x022136b8, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_022110e4(void *);
extern char data_ov004_02251b40;
extern char data_ov004_02251bec;

void *func_ov004_022136b8(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02251b40;
    *(void **) ((char *) this + 0xec) = &data_ov004_02251bec;
    return this;
}
