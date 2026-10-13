/* func_ov125_0229fb7c @ 0x0229fb7c, 0x54 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov125_0229fb34(char *);
extern int func_ov125_0229fb1c(char *);
extern void func_ov125_0229f928(char *);
extern void func_ov002_0220a0b4(char *, int, int);
extern void func_ov002_0220a374(char *, int);

void func_ov125_0229fb7c(char *obj)
{
    int a, b;

    a = func_ov125_0229fb34(obj);
    b = func_ov125_0229fb1c(obj);
    func_ov002_0220a0b4(obj + 0x644, a, b);
    if (*(unsigned char *) (obj + 0x87c) == 8) {
        func_ov002_0220a374(obj + 0x644, 7);
    } else {
        func_ov002_0220a374(obj + 0x644, 1);
    }
    func_ov125_0229f928(obj);
}
