/* func_ov094_0229a958 @ 0x0229a958, 0x44 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229acb0(void *p, unsigned short *s, int t);
extern int func_ov094_0229b088(void *p, int x);
extern int func_ov094_0229b03c(void *p, int x);
extern int func_ov094_0229a8cc(void *p, int a, int b, int c);

int func_ov094_0229a958(void *p, int a, unsigned short b, int c)
{
    unsigned short local;
    int r4;
    int r7;
    int r3;

    local = b;
    r4 = func_ov094_0229acb0(p, &local, c);
    r7 = func_ov094_0229b088((char *) p + 0x184, r4);
    r3 = func_ov094_0229b03c((char *) p + 0x184, r4);
    return func_ov094_0229a8cc(p, a, r7, r3);
}
