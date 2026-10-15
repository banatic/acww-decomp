/* func_ov133_0229b6b8 @ 0x0229b6b8, 0x5c bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern int func_0206fc8c(void);
extern void *func_02099658(void *a);
extern void func_02077d00(void);
extern void *func_02077c3c(void *e);
extern int func_02077e50(void *t);
extern int func_02077e74(void *key, void *u);

int func_ov133_0229b6b8(void *self, void *key)
{
    void *a;
    int skip;
    char *e;
    int i;

    a = func_020984e8();
    skip = func_0206fc8c();
    func_02099658(a);
    func_02077d00();
    asm {
        mov e, r0
    }
    for (i = 0; i < 0x20; e += 0x24, i++)
    {
        if (func_02077e50(func_02077c3c(e)) && i != skip && func_02077e74(key, func_02077c3c(e))) {
            return 1;
        }
    }
    return 0;
}
