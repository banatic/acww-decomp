/* func_0208f4e0 @ 0x0208f4e0, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208effc(void *);
extern void *func_0208f628(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern char data_020e23a0;

void *func_0208f4e0(void *p)
{
    ((unsigned int *) p)[0] = (unsigned int) &data_020e23a0;
    func_0208effc(p);
    func_0208f628((char *) p + 0x4C);
    func_0208a1f4((char *) p + 0x30);
    func_0208a1f4((char *) p + 0x1C);
    func_0208af00(p);
    return p;
}
