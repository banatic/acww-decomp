/* func_020f3340 @ 0x020f3340, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_0213ebd8;
extern void func_020f4514(void *obj);
extern void func_020edb3c(void *obj);

void *func_020f3340(void *obj)
{
    *(unsigned int *) obj = (unsigned int) &data_0213ebd8;
    func_020f4514(obj);
    func_020edb3c(obj);
    return obj;
}
