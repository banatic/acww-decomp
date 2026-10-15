/* func_0209cfb8 @ 0x0209cfb8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206e8b4(void *ptr);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_0209d038(void *);

void *func_0209cfb8(void *obj)
{
    func_0206e8b4((char *) obj + 0x120);
    __cxa_vec_cleanup((void *) (obj), 0x24, 8, (void (*)(void *)) func_0209d038);
    return obj;
}
