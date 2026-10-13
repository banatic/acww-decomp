/* func_020f2d28 @ 0x020f2d28, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4514(void *obj);
extern void func_020edb3c(void *obj);
extern char data_0213ed44;

void *func_020f2d28(void *obj)
{
    *(void **) obj = &data_0213ed44;
    func_020f4514(obj);
    func_020edb3c(obj);
    return obj;
}
