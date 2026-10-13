/* func_ov104_0229d4a8 @ 0x0229d4a8, 0x58 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229da80(char *, int);
extern int func_ov104_0229da70(char *, int);
extern int func_ov104_0229da38(char *, int);
extern int func_ov094_0229b8d8(char *, int);
extern void func_02066830(char *, int);
extern void func_ov094_0229b890(char *, int);

void func_ov104_0229d4a8(char *s, int p2)
{
    int res;
    int res1;

    if (func_ov104_0229da80(s, p2) == 0 && func_ov104_0229da70(s, p2) == 0) {
        return;
    }

    res = func_ov104_0229da38(s, p2);
    s[0xb4] = 1;
    res1 = func_ov094_0229b8d8(s + 0xd58, res);
    func_02066830(s + 0xc0, res1);
    func_ov094_0229b890(s + 0xd58, res);
}
