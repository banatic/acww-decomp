/* func_020eb628 @ 0x020eb628, 0x6c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int DWC_CheckFriendKey(int, int, int);
extern void func_02101164(int, int, int);
extern int DWC_GetGsProfileId(int, int);

int func_020eb628(int a, int b, int c, int d)
{
    if (DWC_CheckFriendKey(a, c, d) && (func_02101164(b, c, d), DWC_GetGsProfileId(a, b) > 0)) {
        return 1;
    }
    return 0;
}
