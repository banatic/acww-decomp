/* func_020eb868 @ 0x020eb868, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned short data_021fbefc;
extern int DWCi_GetProfileIDFromList(int index);

int func_020eb868(int a)
{
    unsigned short s = data_021fbefc;
    if (s < 4) {
        return -1;
    }
    return DWCi_GetProfileIDFromList(a);
}
