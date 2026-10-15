/* func_ov004_02214c10 @ 0x02214c10, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_022110e4(void *);
extern char data_ov004_02252824;
extern char data_ov004_022528d0;

void *func_ov004_02214c10(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02252824;
    *(void **) ((char *) this + 0xec) = &data_ov004_022528d0;
    return this;
}
