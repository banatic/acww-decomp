/* func_ov048_02262aac @ 0x02262aac, 0x2e bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a6ed0(void);
extern int func_020984fc(void *arg0);
extern int DWCi_GsMalloc(int);
extern void func_02099a38(int);

int func_ov048_02262aac(void)
{
    int r5 = func_020a6ed0();
    int r4 = func_020984fc((void *) r5);
    if (DWCi_GsMalloc(r5) == 0) {
        func_02099a38(r4);
        return 1;
    }
    return 0;
}
