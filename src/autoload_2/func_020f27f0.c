/* func_020f27f0 @ 0x020f27f0, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4514(void *p);
extern int data_0213eeb0;

void *func_020f27f0(void *p)
{
    *(int **) p = &data_0213eeb0;
    func_020f4514(p);
    return p;
}
