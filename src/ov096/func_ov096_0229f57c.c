/* func_ov096_0229f57c @ 0x0229f57c, 0x30 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f820(void);
extern int func_ov096_0229f548(int, int);
extern void func_ov094_0229b890(int, int);

void func_ov096_0229f57c(int r4, int r5)
{
    if (func_ov096_0229f820()) {
        func_ov094_0229b890(r4 + 0xdb8, func_ov096_0229f548(r4, r5));
    }
}
