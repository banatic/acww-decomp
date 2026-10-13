/* func_ov142_02299f8c @ 0x02299f8c, 0x18 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov142_02299fbc(void);
extern void func_ov142_02299f5c(int);

void func_ov142_02299f8c(int r0)
{
    int r4 = r0;
    if (func_ov142_02299fbc() == 0) {
        func_ov142_02299f5c(r4);
    }
}
