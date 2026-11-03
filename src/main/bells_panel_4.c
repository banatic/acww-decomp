/* bells_panel_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208ba30 @ 0x0208ba30, 0x22 bytes, Thumb
 * func_0208ba10 @ 0x0208ba10, 0x1e bytes, Thumb
 */

extern void func_0208b800(void *);
extern void func_0208b648(void *);
extern void func_0208b9a8(void *);
extern void func_0208b748(void *param1, int param2);
extern void *func_0208a144(void *param1);
extern void func_0208b824(void *param1);

void func_0208ba30(void *param)
{
    char *p = (char *) param;
    p[0x80] = 0;
    func_0208b800(param);
    func_0208b648(param);
    func_0208b9a8(param);
}

void func_0208ba10(void *param1)
{
    func_0208b748(param1, 0);
    func_0208a144((char *) param1 + 0xc);
    func_0208b824(param1);
}
