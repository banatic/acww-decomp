/* func_020ea3bc @ 0x020ea3bc, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *);
extern char data_0213e660;

void *func_020ea3bc(void *p)
{
    *(void **) p = (void *) &data_0213e660;
    func_020edb3c(p);
    return p;
}
