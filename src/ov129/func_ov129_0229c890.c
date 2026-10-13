/* func_ov129_0229c890 @ 0x0229c890, 0x28 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b8ac(char *p, int n);
extern void func_ov129_0229c820(char *p);
extern void func_0208e5cc(char *p);

void func_ov129_0229c890(char *p)
{
    if (func_ov002_0220b8ac(p + 0xb8, 0)) {
        func_ov129_0229c820(p);
        func_0208e5cc(p + 0x3a0);
    }
}
