/* func_02064210 @ 0x02064210, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064170(void *);
extern void func_020a8874(void *, void *, int);
extern void func_020a8a70(void *, void *, int, int);
extern void func_02064158(void *);

void func_02064210(void *param0, void *param1)
{
    char local[0x1c];
    void *r5;
    void *r4;

    r5 = param0;
    r4 = param1;
    func_02064170(local);
    func_020a8874(local, (char *) r5 + 2, 6);
    func_020a8a70(r4, local, 0, 0);
    func_02064158(local);
}
