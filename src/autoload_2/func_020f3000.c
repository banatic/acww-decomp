/* func_020f3000 @ 0x020f3000, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_0213eca8;
extern void func_020f4514(void *);
extern void func_020edb3c(void *);

void *func_020f3000(void *p)
{
    *(void **) p = &data_0213eca8;
    func_020f4514(p);
    func_020edb3c(p);
    return p;
}
