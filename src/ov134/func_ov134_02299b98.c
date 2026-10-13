/* func_ov134_02299b98 @ 0x02299b98, 0x32 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a58c(void *);
extern int func_ov002_0220a574(void *);

int func_ov134_02299b98(void *r0, int r1, int r2)
{
    int r5 = (int) r0;
    int r4 = r2;
    int result;
    void *p = (void *) (r5 + 0x18);
    if (func_ov002_0220a58c(p) != 0) {
        *(int *) (r5 + 0x68) = *(int *) (r5 + 0x64) - r4;
        func_ov002_0220a574((void *) (r5 + 0x18));
        *(int *) (r5 + 0x6c) = *(int *) (r5 + 0x64);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
