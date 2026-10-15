/* func_02080a94 @ 0x02080a94, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int *func_02082164(void *);
extern void func_0205195c(void *);
extern int func_020a87e0(void *, void *);
extern void func_02080a7c(void *, void *);
extern void *func_0208214c(void *);

void func_02080a94(void *param0, void *param1)
{
    char sp[0x1c];
    void *r5 = param0;
    void *r4 = param1;

    func_02082164(sp);
    func_0205195c(sp);
    func_020a87e0(sp, r4);
    func_02080a7c(r5, sp);
    func_0208214c(sp);
}
