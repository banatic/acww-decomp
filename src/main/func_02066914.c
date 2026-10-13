/* func_02066914 @ 0x02066914, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c1c(void *);

void func_02066914(void *param0, int param1)
{
    void *r4 = param0;
    int r5 = param1;
    func_020a8c1c((char *) r4 + 0x20);
    *(int *) ((char *) r4 + 0x2c) = r5;
    *(char *) ((char *) r4 + 0x44) = 1;
}
