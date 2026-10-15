/* func_020afb24 @ 0x020afb24, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);
extern int func_020afb48(void *, void *);

int func_020afb24(void *param)
{
    void *sp[2];
    sp[0] = 0;
    sp[1] = 0;
    func_0209e474(sp);
    return func_020afb48(param, sp);
}
