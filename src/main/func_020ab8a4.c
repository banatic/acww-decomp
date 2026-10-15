/* func_020ab8a4 @ 0x020ab8a4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8c38(void *this);
extern void func_020edb3c(void *this);
extern char data_020e3f9c;

void *func_020ab8a4(void *this)
{
    *(void **) this = &data_020e3f9c;
    func_020a8c38(this);
    func_020edb3c(this);
    return this;
}
