/* func_020f3f64 @ 0x020f3f64, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4514(void *this);
extern char data_0213ef80;

void *func_020f3f64(void *this)
{
    *(void **) this = (void *) &data_0213ef80;
    func_020f4514(this);
    return this;
}
