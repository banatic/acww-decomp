/* func_ov004_02212fc8 @ 0x02212fc8, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_022110e4(void *);
extern char data_ov004_0225130c;
extern char data_ov004_022513b8;

void *func_ov004_02212fc8(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_0225130c;
    *(void **) ((char *) this + 0xec) = &data_ov004_022513b8;
    return this;
}
