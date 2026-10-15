/* func_ov048_022615a4 @ 0x022615a4, 0x38 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov048_022614ac(void);
extern int func_0209fdd4(void);
extern void func_ov048_022616b8(void *, int);
extern void func_020eb9fc(void);

void func_ov048_022615a4(void *r0)
{
    void *r4 = r0;
    if (func_ov048_022614ac()) {
        func_020eb9fc();
        func_ov048_022616b8(r4, *(int *) ((char *) r4 + 0xb4) + 1);
    } else if (func_0209fdd4()) {
        func_ov048_022616b8(r4, *(int *) ((char *) r4 + 0xb4) + 1);
    }
}
