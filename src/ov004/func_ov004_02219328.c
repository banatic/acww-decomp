/* func_ov004_02219328 @ 0x02219328, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_022110e4(void *);
extern char data_ov004_022518e8;
extern char data_ov004_02251994;

void *func_ov004_02219328(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_022518e8;
    *(void **) ((char *) this + 0xec) = &data_ov004_02251994;
    return this;
}
