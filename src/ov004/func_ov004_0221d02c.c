/* func_ov004_0221d02c @ 0x0221d02c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0221d08c(void);
extern int func_020819bc(void);

int func_ov004_0221d02c(void)
{
    if (func_ov004_0221d08c() != 0) {
        if (func_020819bc() == 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}
