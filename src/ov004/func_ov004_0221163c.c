/* func_ov004_0221163c @ 0x0221163c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_022110e4(void *);
extern char data_ov004_022526f8;
extern char data_ov004_022527a4;

void *func_ov004_0221163c(void *this)
{
    func_ov004_022110e4(this);
    *(void **) this = &data_ov004_022526f8;
    *(void **) ((char *) this + 0xec) = &data_ov004_022527a4;
    return this;
}
