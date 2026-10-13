/* func_020f2a18 @ 0x020f2a18, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213ee14;
extern void func_020f4514(void *);
extern void func_020edb3c(void *);

void *func_020f2a18(void *obj)
{
    *(void **) obj = &data_0213ee14;
    func_020f4514(obj);
    func_020edb3c(obj);
    return obj;
}
