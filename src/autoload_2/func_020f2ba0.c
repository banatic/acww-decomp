/* func_020f2ba0 @ 0x020f2ba0, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4514(void *p);
extern void func_020edb3c(void *p);
extern char data_0213edac;

void *func_020f2ba0(void *this)
{
    *(void **) this = (void *) &data_0213edac;
    func_020f4514(this);
    func_020edb3c(this);
    return this;
}
