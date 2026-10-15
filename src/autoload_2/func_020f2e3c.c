/* func_020f2e3c @ 0x020f2e3c, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f45c4(void *this);
extern unsigned int data_0213ed10;

void *func_020f2e3c(void *this)
{
    func_020f45c4(this);
    *(unsigned int *) this = (unsigned int) &data_0213ed10;
    *((unsigned char *) this + 4) = 42;
    return this;
}
