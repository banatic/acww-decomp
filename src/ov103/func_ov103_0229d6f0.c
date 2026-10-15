/* func_ov103_0229d6f0 @ 0x0229d6f0, 0x34 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(int a1, int a2);
extern unsigned char *func_ov002_02208098(int a1, unsigned char value);
extern int func_ov002_0220b498(void *);
extern void func_ov103_0229c30c(int a1);

void func_ov103_0229d6f0(int a1)
{
    int v1;
    int v2;

    v1 = func_ov002_02208054(a1, 1);
    if (v1 != 0) {
        func_ov002_02208098(a1, 7);
        return;
    }
    v2 = func_ov002_0220b498((void *) (a1 + 0x2b10));
    if (v2 != 0) {
        func_ov103_0229c30c(a1);
    }
}
