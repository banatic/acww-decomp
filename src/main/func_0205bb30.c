/* func_0205bb30 @ 0x0205bb30, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205bbdc(void *);
extern char data_020dd3a4;

void *func_0205bb30(void *this)
{
    *(void **) this = (void *) &data_020dd3a4;
    func_0205bbdc(this);
    return this;
}
