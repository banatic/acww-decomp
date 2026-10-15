/* func_ov048_02261540 @ 0x02261540, 0x38 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov048_022614ac(void);
extern void func_020eb9fc(void);
extern int func_0209fdac(void);
extern void func_ov048_022616b8(void *p, int val);

void func_ov048_02261540(void *p)
{
    if (func_ov048_022614ac()) {
        func_020eb9fc();
        func_ov048_022616b8(p, (*(int *) ((char *) p + 0xb4) + 1));
    } else {
        if (func_0209fdac()) {
            func_ov048_022616b8(p, (*(int *) ((char *) p + 0xb4) + 1));
        }
    }
}
