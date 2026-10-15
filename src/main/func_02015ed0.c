/* func_02015ed0 @ 0x02015ed0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8228(void *);
extern int func_020b44bc(void *, void *);
extern void func_02068404(void *, void *, void *);
extern void *func_020a8210(void *);

void func_02015ed0(void *param0, void *param1, void *param2)
{
    char sp[0x60];
    void *r5 = param0;
    void *r4 = param1;
    void *r6 = param2;

    func_020a8228(sp);
    func_020b44bc(sp, r4);
    func_02068404(*(void **) ((char *) r5 + 0x40), r6, sp);
    func_020a8210(sp);
}
