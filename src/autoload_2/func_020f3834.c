/* func_020f3834 @ 0x020f3834, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4514(void *obj);
extern char data_0213eaa0;

void *func_020f3834(void *obj)
{
    *(void **) obj = &data_0213eaa0;
    func_020f4514(obj);
    return obj;
}
