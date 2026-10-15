/* func_02081bc4 @ 0x02081bc4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020820a0(void *);
extern void func_02081ba0(void *, void *);
extern void func_020a8874(void *, void *, int);
extern int func_020a8a70(void *, void *, int, int);
extern void *func_02082088(void *);

void *func_02081bc4(void *p0, void *p1)
{
    char local[0x24];
    func_020820a0(local);
    func_02081ba0(p0, local);
    func_020a8874(local, (char *) p0 + 0x2a, 0xa);
    func_020a8a70(p1, local, 0, 0);
    return func_02082088(local);
}
