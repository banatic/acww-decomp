/* func_020b18c4 @ 0x020b18c4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e4278;
extern void *func_020a887c(void *this);
extern void func_020edb3c(void *this);

void *func_020b18c4(void *this)
{
    *((void **) this) = &data_020e4278;
    func_020a887c(this);
    func_020edb3c(this);
    return this;
}
