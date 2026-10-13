/* func_020780d0 @ 0x020780d0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8cac(void *);
extern void func_020a8c1c(void *);
extern char data_020e1888;

void *func_020780d0(void *a)
{
    func_020a8cac(a);
    *(void **) a = (void *) &data_020e1888;
    func_020a8c1c(a);
    return a;
}
