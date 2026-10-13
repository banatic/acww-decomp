/* func_02010bf0 @ 0x02010bf0, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205cf28(int);
extern void func_02010b50(int, int *, int);

void func_02010bf0(int r0, int *r1, int r2)
{
    int r4;
    int r5 = r0;
    int r6 = r2;
    int sp0;
    int r0_val;

    r4 = *(int *) (r5 + 0x76c);
    r0_val = func_0205cf28(*r1);
    sp0 = r0_val;
    if (r0_val == 0x16f && r4 != 0) {
        sp0 = 0;
    }
    if (sp0 != 0x16f) {
        func_02010b50(r5, &sp0, r6);
    }
}
