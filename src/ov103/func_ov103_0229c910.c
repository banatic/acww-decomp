/* func_ov103_0229c910 @ 0x0229c910, 0x54 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov103_0229cdfc(char *a, char *b);
extern int func_ov103_0229cde8(char *a, char *b);
extern int func_ov094_0229b8d8(char *ptr, int v);
extern int func_02066830(char *ptr, int v);
extern void func_ov094_0229b890(char *ptr, int v);

void func_ov103_0229c910(char *a, char *b)
{
    if (func_ov103_0229cdfc(a, b) != 0) {
        int tmp = func_ov103_0229cde8(a, b);
        a[0x2da0] = 1;
        func_02066830(a + 0x2ba0, func_ov094_0229b8d8(a + 0x0b2c, tmp));
        func_ov094_0229b890(a + 0x0b2c, tmp);
    }
}
