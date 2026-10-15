/* func_020708b4 @ 0x020708b4, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020707d0(void *);
extern int func_020a87e0(void *, void *);
extern int func_0205182c(void *, void *, int);
extern void *func_020707b8(void *);

void func_020708b4(void *param0, void *param1)
{
    char buffer[0x64];
    func_020707d0(buffer);
    func_020a87e0(buffer, param0);
    func_0205182c(buffer, param1, 0x29);
    func_020707b8(buffer);
}
