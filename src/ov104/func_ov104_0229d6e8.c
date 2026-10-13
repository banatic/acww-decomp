/* func_ov104_0229d6e8 @ 0x0229d6e8, 0x3c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229da80(char *p, void *q);
extern int func_ov104_0229da70(char *p, void *q);
extern int func_ov104_0229da38(char *p, void *q);
extern void func_ov094_0229b938(char *p, int n);

void func_ov104_0229d6e8(char *p, void *q)
{
    if (func_ov104_0229da80(p, q) != 0 || func_ov104_0229da70(p, q) != 0) {
        func_ov094_0229b938(p + 0x0d58, func_ov104_0229da38(p, q));
    }
}
