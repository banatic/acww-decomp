/* func_0208ba30 @ 0x0208ba30, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208b800(void *);
extern void func_0208b648(void *);
extern void func_0208b9a8(void *);

void func_0208ba30(void *param)
{
    char *p = (char *) param;
    p[0x80] = 0;
    func_0208b800(param);
    func_0208b648(param);
    func_0208b9a8(param);
}
