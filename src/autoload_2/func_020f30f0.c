/* func_020f30f0 @ 0x020f30f0, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f4514(void *p);
extern int data_0213ec74;

void *func_020f30f0(void *p)
{
    *(void **) p = (void *) &data_0213ec74;
    func_020f4514(p);
    return p;
}
