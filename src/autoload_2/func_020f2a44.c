/* func_020f2a44 @ 0x020f2a44, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213ee14;
extern void *func_020f4514(void *);

void *func_020f2a44(void *p)
{
    *(void **) p = (void *) &data_0213ee14;
    func_020f4514(p);
    return p;
}
