/* func_02081b00 @ 0x02081b00, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205195c(void *);
extern void func_020a8874(void *, void *, int);

void func_02081b00(void *arg0, void *arg1)
{
    void *r5;
    void *r4;
    void *sp_4;

    r5 = arg0;
    r4 = arg1;
    func_0205195c(r4);
    r5 = (char *) r5 + 0x3e;
    func_020a8874(r4, r5, 0xa);
    return;
}
