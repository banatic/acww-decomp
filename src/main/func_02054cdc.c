/* func_02054cdc @ 0x02054cdc, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056e84(void *ptr);
extern void func_02055124(void *ptr);

void func_02054cdc(void *arg)
{
    void *r4 = arg;
    func_02056e84((char *) r4 + 0xb8);
    func_02055124(r4);
}
