/* func_020a9db0 @ 0x020a9db0, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020aa2e4(void *);

void func_020a9db0(void *arg0)
{
    void *r4;
    void *r0;

    r4 = arg0;
    r0 = (char *) arg0 + 0xc8;
    func_020aa2e4(r0);
    r0 = (char *) r4 + 0xc8;
    *(void **) r4 = r0;
}
