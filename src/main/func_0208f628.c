/* func_0208f628 @ 0x0208f628, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e2388;
extern void *func_020a8c38(void *this);

void *func_0208f628(void *this)
{
    *(void **) this = &data_020e2388;
    func_020a8c38(this);
    return this;
}
