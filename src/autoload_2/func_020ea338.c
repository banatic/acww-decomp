/* func_020ea338 @ 0x020ea338, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213e608;
extern void func_020ea3ac(void *obj);

void *func_020ea338(void *obj)
{
    *(void **) obj = &data_0213e608;
    func_020ea3ac(obj);
    return obj;
}
