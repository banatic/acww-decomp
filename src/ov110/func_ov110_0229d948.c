/* func_ov110_0229d948 @ 0x0229d948, 0x44 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208098(int, int);
extern int func_0208e4bc(int);
extern void func_ov002_022096d8(int, int);
extern int func_ov002_0220909c(int);
extern void func_ov110_0229ca48(int);

void func_ov110_0229d948(int arg0)
{
    if (func_ov002_0220909c(arg0 + 0x2344) != 0) {
        func_ov002_022096d8(arg0 + 0x2344, 0);
        if (func_0208e4bc(arg0 + 0x22e0) != 0) {
            func_ov110_0229ca48(arg0);
        }
        func_ov002_02208098(arg0, 0x13);
    }
}
