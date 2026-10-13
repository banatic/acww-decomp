/* func_020f2b08 @ 0x020f2b08, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4514(void *p);
extern char data_0213ede0;

void *func_020f2b08(void *p)
{
    *(void **) p = &data_0213ede0;
    func_020f4514(p);
    return p;
}
