/* func_0206e388 @ 0x0206e388, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206dd8c(void *);
extern void *func_0206dd6c(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

void *func_0206e388(void *param)
{
    func_0206dd8c(param);
    func_0206dd8c((char *) param + 0x74);
    __cxa_vec_ctor((void *) ((char *) param + 0xe8), 4, 0x74, (((void (*)(void *)) func_0206dd8c)),
                   (((void (*)(void *)) func_0206dd6c)));
    return param;
}
