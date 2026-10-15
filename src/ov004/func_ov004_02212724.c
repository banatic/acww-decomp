/* func_ov004_02212724 @ 0x02212724, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_022110e4(void *);
extern char data_ov004_02250d30;
extern char data_ov004_02250ddc;

void *func_ov004_02212724(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02250d30;
    *(void **) ((char *) this + 0xec) = &data_ov004_02250ddc;
    return this;
}
