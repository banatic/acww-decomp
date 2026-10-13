/* func_020eb8a0 @ 0x020eb8a0, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned short data_021fbefc;
extern int DWCi_GetFriendListIndex(int a);

int func_020eb8a0(int a)
{
    if (data_021fbefc < 4) {
        return -1;
    }
    return DWCi_GetFriendListIndex(a);
}
