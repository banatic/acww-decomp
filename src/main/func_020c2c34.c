/* func_020c2c34 @ 0x020c2c34, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020c338c(void *ptr);
extern void *func_0202ee5c(void *ptr);
extern char data_020e7ea4;

void *func_020c2c34(void *obj)
{
    *(void **) obj = &data_020e7ea4;
    func_020c338c((char *) obj + 0x658);
    func_0202ee5c(obj);
    return obj;
}
