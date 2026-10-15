/* func_ov004_02216c20 @ 0x02216c20, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_022110e4(void *);
extern char data_ov004_02251d98;
extern char data_ov004_02251e44;

void *func_ov004_02216c20(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_02251d98;
    *(void **) ((char *) this + 0xec) = &data_ov004_02251e44;
    return this;
}
