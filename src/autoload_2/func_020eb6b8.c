/* func_020eb6b8 @ 0x020eb6b8, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int DWCi_Acc_IsDirty(void *object);
extern void func_02101234(int);

int func_020eb6b8(int arg0)
{
    if (DWCi_Acc_IsDirty((void *) arg0) == 0) {
        return 0;
    }
    func_02101234(arg0);
    return 1;
}
