/* func_020f3440 @ 0x020f3440, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f4514(void *this);
extern int data_0213eba4;

void *func_020f3440(void *this)
{
    *(void **) this = &data_0213eba4;
    func_020f4514(this);
    return this;
}
