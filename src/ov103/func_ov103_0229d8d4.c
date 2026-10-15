/* func_ov103_0229d8d4 @ 0x0229d8d4, 0x38 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_022091cc(void *object);
extern void func_ov094_0229a05c(void *object);
extern int func_ov002_02207d5c(void *object);

extern void func_ov103_0229ca9c(void *);

void func_ov103_0229d8d4(void *r0)
{
    void *r4 = r0;
    func_ov002_022091cc((char *) r4 + 0x22d8);
    func_ov094_0229a05c((char *) r4 + 0xb54);
    if (func_ov002_02207d5c((char *) r4 + 0x218c)) {
        func_ov103_0229ca9c(r4);
    }
}
