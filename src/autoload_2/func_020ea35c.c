/* func_020ea35c @ 0x020ea35c, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ea3ac(void *);
extern void func_020edb3c(void *);
extern char data_0213e5b0;

void *func_020ea35c(void *obj)
{
    *(void **) obj = &data_0213e5b0;
    func_020ea3ac(obj);
    func_020edb3c(obj);
    return obj;
}
