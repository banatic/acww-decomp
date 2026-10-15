/* func_ov004_02213d30 @ 0x02213d30, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_022110e4(void *);
extern char data_ov004_02251ff0;
extern char data_ov004_0225209c;

void *func_ov004_02213d30(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02251ff0;
    *(void **) ((char *) this + 0xec) = &data_ov004_0225209c;
    return this;
}
