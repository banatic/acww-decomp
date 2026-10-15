/* func_020f38f8 @ 0x020f38f8, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f4514(void *this);
extern unsigned int data_0213ea6c;

void *func_020f38f8(void *this)
{
    *(void **) this = (void *) &data_0213ea6c;
    func_020f4514(this);
    return this;
}
