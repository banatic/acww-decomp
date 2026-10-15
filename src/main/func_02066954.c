/* func_02066954 @ 0x02066954, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a8be4(void *, int);

void func_02066954(void *r0, int r1, int r2)
{
    void *r4 = r0;
    int r5 = r2;

    func_020a8be4((char *) r0 + 0x20, r1);
    *(int *) ((char *) r4 + 0x2c) = r5;
    *(char *) ((char *) r4 + 0x44) = 0;
}
