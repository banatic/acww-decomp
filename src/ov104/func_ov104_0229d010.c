/* func_ov104_0229d010 @ 0x0229d010, 0x7c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229c364(char *p, int x);
extern void func_ov002_02208c58(char *a, char *b, int c);
extern int func_ov104_0229d8a8(char *p, unsigned char x);
extern int func_ov104_0229d858(char *p, unsigned char x);
extern void func_ov002_02209874(char *a, char *b, int c);
extern void func_ov002_02209910(char *a, int b, int c);
extern void func_ov002_0220970c(char *a, int b);
extern void func_ov002_02208098(char *a, int b);

void func_ov104_0229d010(char *p, int flag)
{
    int res1, res2, res3;
    res1 = func_ov104_0229c364(p, 0x8000);
    func_ov002_02208c58(p + 0x2504, p + 0x28ec, res1);
    res2 = func_ov104_0229d8a8(p, *(unsigned char *) (p + 0xb9));
    res3 = func_ov104_0229d858(p, *(unsigned char *) (p + 0xb9));
    if (flag) {
        func_ov002_02209874(p + 0x2504, p + 0x23b8, res3);
    } else {
        func_ov002_02209910(p + 0x2504, res2, res3);
    }
    func_ov002_0220970c(p + 0x2504, 0);
    func_ov002_02208098(p, 0x16);
}
