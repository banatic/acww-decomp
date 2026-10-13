/* func_ov048_02260474 @ 0x02260474, 0x38 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201a3e4(int);
extern int func_020c18c4(void);

int func_ov048_02260474(int param)
{
    int r4;
    int r0;

    r4 = param;
    r0 = func_0201a3e4(r4 + 0x2ac);
    if (r0 == 0xba) {
        if (func_020c18c4() != 0) {
            r0 = *(int *) (*(int *) (r4 + 0x698) + 4);
            if (r0 == 2) {
                return 1;
            }
        }
    }
    return 0;
}
