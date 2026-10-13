/* func_ov004_0221d050 @ 0x0221d050, 0x16 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0221d08c(void);
extern void func_02081974(void);

void func_ov004_0221d050(void)
{
    if (func_ov004_0221d08c() != 0) {
        func_02081974();
    }
}
