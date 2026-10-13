/* func_020a9278 @ 0x020a9278, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e3de4;
extern void func_020a941c(void *obj, void *ptr);
extern void func_020edb3c(void *obj);

void *func_020a9278(void *obj)
{
    ((void **) obj)[0] = &data_020e3de4;
    func_020a941c(obj, &data_020e3de4);
    func_020edb3c(obj);
    return obj;
}
