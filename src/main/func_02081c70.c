/* func_02081c70 @ 0x02081c70, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0205195c(void *);
extern void func_020a8874(void *, void *, int);

void func_02081c70(void *param0, void *param1)
{
    void *r5;
    void *r4;

    r5 = param0;
    r4 = param1;
    func_0205195c(r4);
    func_020a8874(r4, (char *) r5 + 0x1e, 6);
}
