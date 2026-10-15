/* func_0206da60 @ 0x0206da60, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020df210;
extern void *func_020a8c38(void *obj);
extern void func_020edb3c(void *obj);

void *func_0206da60(void *obj)
{
    *(void **) obj = &data_020df210;
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}
