/* func_020641e0 @ 0x020641e0, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02064170(void *);
extern int func_020a87e0(void *, void *);
extern void func_02064128(void *, void *, int);
extern void *func_02064158(void *);

void func_020641e0(void *param0, void *param1)
{
    char local[0x1c];
    void *r5 = param0;
    void *r4 = param1;

    func_02064170(local);
    func_020a87e0(local, r4);
    func_02064128(local, (char *) r5 + 2, 6);
    func_02064158(local);
}
