/* func_0206e388 @ 0x0206e388, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206dd8c(void *p);
extern void func_0206dd6c(void *p);
extern void func_02138d6c(void *p, int a, int b, void (*f)(void *), void (*g)(void *));

void *func_0206e388(void *param)
{
    func_0206dd8c(param);
    func_0206dd8c((char *) param + 0x74);
    func_02138d6c((char *) param + 0xe8, 4, 0x74, func_0206dd8c, func_0206dd6c);
    return param;
}
