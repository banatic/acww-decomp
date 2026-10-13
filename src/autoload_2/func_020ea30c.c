/* func_020ea30c @ 0x020ea30c, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_0213e608;
extern void func_020ea3ac(void *obj);
extern void func_020edb3c(void *obj);

void *func_020ea30c(void *obj)
{
    *(void **) obj = (void *) &data_0213e608;
    func_020ea3ac(obj);
    func_020edb3c(obj);
    return obj;
}
