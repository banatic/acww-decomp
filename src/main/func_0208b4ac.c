/* func_0208b4ac @ 0x0208b4ac, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208b514(unsigned int value);
extern void func_0208b508(void);
extern void func_0208b090(void *p);
extern void func_0208dd68(void *p);
extern void func_0208d164(void *p);
extern void func_0208c020(void *p);
extern void func_0208ba30(void *p);

void func_0208b4ac(void *p)
{
    func_0208b514((unsigned int) p);
    func_0208b508();
    func_0208b090(p);
    func_0208dd68((char *) p + 8);
    func_0208d164((char *) p + 0xe0);
    func_0208c020((char *) p + 0x1c4);
    func_0208ba30((char *) p + 0x2c4);
    *((char *) p + 0x34a) = 0;
}
