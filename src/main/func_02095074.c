/* func_02095074 @ 0x02095074, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02094f7c(void *);
extern void func_020a8874(void *, void *, int);
extern int func_020a8a70(void *, void *, int, int);
extern void *func_02094f64(void *);

void *func_02095074(void *param0, void *param1)
{
    unsigned char sp[0x1c];
    void *r5 = param0;
    void *r4 = param1;

    func_02094f7c(sp);
    func_020a8874(sp, (char *) r5 + 0x10, 6);
    func_020a8a70(r4, sp, 0, 0);
    return func_02094f64(sp);
}
