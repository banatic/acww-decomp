/* func_020a254c @ 0x020a254c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066994(void *);
extern void func_020edb3c(void *);
extern char data_020e3b38;

void *func_020a254c(void *this)
{
    *(void **) this = &data_020e3b38;
    func_02066994(this);
    func_020edb3c(this);
    return this;
}
