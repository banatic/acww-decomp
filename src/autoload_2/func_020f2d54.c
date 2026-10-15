/* func_020f2d54 @ 0x020f2d54, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213ed44;
extern void *func_020f4514(void *p);

void *func_020f2d54(void *p)
{
    *(void **) p = &data_0213ed44;
    func_020f4514(p);
    return p;
}
