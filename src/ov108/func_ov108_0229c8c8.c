/* func_ov108_0229c8c8 @ 0x0229c8c8, 0x50 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov108_0229cd70(void *a, void *b);
extern int func_ov108_0229cd5c(void *a, void *b);
extern int func_ov094_0229b8d8(void *a, int b);
extern void func_02066830(void *a, int b);
extern void func_ov094_0229b890(void *a, int b);

void func_ov108_0229c8c8(void *a, void *b)
{
    if (func_ov108_0229cd70(a, b) != 0) {
        int ret, v;
        ret = func_ov108_0229cd5c(a, b);
        *((char *) a + 0x2ac) = 1;
        v = func_ov094_0229b8d8((char *) a + 0xd50, ret);
        func_02066830((char *) a + 0xac, v);
        func_ov094_0229b890((char *) a + 0xd50, ret);
    }
}
