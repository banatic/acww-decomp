/* func_02081c40 @ 0x02081c40, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094f7c(void *);
extern void func_020a87e0(void *, void *);
extern void func_02094f34(void *, void *, int);
extern void func_02094f64(void *);

void func_02081c40(void *param0, void *param1)
{
    char sp[0x1c];
    void *r5;
    void *r4;

    r5 = param0;
    r4 = param1;
    func_02094f7c(sp);
    func_020a87e0(sp, r4);
    func_02094f34(sp, (char *) r5 + 0x1e, 6);
    func_02094f64(sp);
}
