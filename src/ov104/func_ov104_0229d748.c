/* func_ov104_0229d748 @ 0x0229d748, 0x50 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229da80(int p1, int p2);
extern int func_ov104_0229da70(int p1, int p2);
extern int func_ov104_0229da38(int p1, int p2);
extern void func_ov104_0229d798(int p1);
extern void func_ov094_0229b950(void *p, int v);
extern void func_ov094_0229ab5c(void *p);

void func_ov104_0229d748(void *p1, void *p2)
{
    volatile int unused;
    if (func_ov104_0229da80((int) p1, (int) p2) || func_ov104_0229da70((int) p1, (int) p2)) {
        int t = func_ov104_0229da38((int) p1, (int) p2);
        func_ov094_0229b950((char *) p1 + 0xd58, t);
        func_ov094_0229ab5c((char *) p1 + 0x2f8);
    } else {
        func_ov104_0229d798((int) p1);
    }
}
