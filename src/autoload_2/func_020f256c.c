/* func_020f256c @ 0x020f256c, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_0213ef4c;
extern void *func_020f4514(void *a);

void *func_020f256c(void *p)
{
    *(void **) p = &data_0213ef4c;
    func_020f4514(p);
    return p;
}
