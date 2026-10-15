/* func_020f3680 @ 0x020f3680, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_0213eb08;
extern void *func_020f4514(void *p);
extern void func_020edb3c(void *p);

void *func_020f3680(void *p)
{
    *(void **) p = (void *) &data_0213eb08;
    func_020f4514(p);
    func_020edb3c(p);
    return p;
}
