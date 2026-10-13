/* func_0206dd6c @ 0x0206dd6c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020df258[];
extern void func_0206dcec(void *p);
extern void func_020a8c38(void *p);

void *func_0206dd6c(void *p)
{
    *(void **) p = (void *) data_020df258;
    func_0206dcec(p);
    func_020a8c38(p);
    return p;
}
