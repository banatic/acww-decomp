/* func_ov004_02218ee8 @ 0x02218ee8, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022110e4(void *);
extern char data_ov004_022510b4;
extern char data_ov004_02251160;

void *func_ov004_02218ee8(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_022510b4;
    *(void **) ((char *) this + 0xec) = &data_ov004_02251160;
    return this;
}
