/* func_ov129_0229c4b8 @ 0x0229c4b8, 0x68 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov129_0229c468(char *p);
extern int func_ov129_0229c418(char *p);
extern int func_ov129_0229c548(char *p);
extern int func_ov129_0229c520(char *p);
extern void func_ov129_0229c348(char *p);
extern void func_ov002_0220a0b4(char *p, int a, int b);
extern void func_ov002_0220a374(char *p, int n);

void func_ov129_0229c4b8(char *p)
{
    int a = func_ov129_0229c468(p);
    int b = func_ov129_0229c418(p);
    func_ov002_0220a0b4(p + 0x3a0, a, b);
    if (func_ov129_0229c548(p)) {
        func_ov002_0220a374(p + 0x3a0, 1);
    } else if (func_ov129_0229c520(p)) {
        func_ov002_0220a374(p + 0x3a0, 7);
    } else {
        func_ov002_0220a374(p + 0x3a0, 0xd);
    }
    func_ov129_0229c348(p);
}
