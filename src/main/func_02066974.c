/* func_02066974 @ 0x02066974, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8170(void *param1);
extern void func_020a8c1c(void *param2);

void func_02066974(void *param0)
{
    void *r4 = param0;
    func_020a8170(r4);
    func_020a8c1c((char *) r4 + 0x20);
    *(int *) ((char *) r4 + 0x40) = 0;
    *(char *) ((char *) r4 + 0x44) = 0;
}
