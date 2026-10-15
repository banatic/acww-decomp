/* func_020f3198 @ 0x020f3198, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f4514(void *);
extern void func_020edb3c(int argument0);
extern char data_0213e9d0;

void *func_020f3198(void *p)
{
    *(void **) p = (void *) &data_0213e9d0;
    func_020f4514(p);
    func_020edb3c((int) p);
    return p;
}
