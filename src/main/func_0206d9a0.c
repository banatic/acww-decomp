/* func_0206d9a0 @ 0x0206d9a0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020df1d0;
extern void *func_020a8c38(void *);
extern void func_020edb3c(void *);

void *func_0206d9a0(void *obj)
{
    *(void **) obj = &data_020df1d0;
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}
