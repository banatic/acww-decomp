/* func_020f38cc @ 0x020f38cc, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213ea6c;
extern void func_020f4514(void *p);
extern void func_020edb3c(void *p);

void *func_020f38cc(void *p)
{
    *(int **) p = &data_0213ea6c;
    func_020f4514(p);
    func_020edb3c(p);
    return p;
}
