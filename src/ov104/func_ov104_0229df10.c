/* func_ov104_0229df10 @ 0x0229df10, 0x3c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208e28(const char *addr);
extern int func_0206fe54(void);
extern void func_ov104_0229d1ec(char *p);
extern void func_ov002_02208098(char *p, int param);

void func_ov104_0229df10(char *p)
{
    if (func_ov002_02208e28(p + 0x2504)) {
        if (func_0206fe54()) {
            func_ov104_0229d1ec(p);
            func_ov002_02208098(p, 11);
        } else {
            func_ov002_02208098(p, 6);
        }
    }
}
