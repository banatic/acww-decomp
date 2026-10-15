/* func_020f3d74 @ 0x020f3d74, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f3f14(void *);
extern void func_020edb3c(void *);
extern int data_0213e99c;

void *func_020f3d74(void *obj)
{
    *(void **) obj = (void *) &data_0213e99c;
    func_020f3f14(obj);
    func_020edb3c(obj);
    return obj;
}
