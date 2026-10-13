/* func_020f3f38 @ 0x020f3f38, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213ef80;
extern void func_020f4514(void *obj);
extern void func_020edb3c(void *obj);

void *func_020f3f38(void *obj)
{
    *(void **) obj = (void *) &data_0213ef80;
    func_020f4514(obj);
    func_020edb3c(obj);
    return obj;
}
