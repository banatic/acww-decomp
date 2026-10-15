/* func_020c3e6c @ 0x020c3e6c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void *);
extern void func_020c3dac(void *param1, int param2);

int func_020c3e6c(void *param0)
{
    int result;
    void *r4 = param0;
    int r0;

    if (func_0202ec58(param0) == 0) {
        return 0;
    }

    func_020c3dac(r4, 0);
    r0 = *(short *) ((char *) r4 + 0x8e);
    *(short *) ((char *) r4 + 0x710) = r0;
    return 1;
}
