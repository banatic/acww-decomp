/* func_020b2fc4 @ 0x020b2fc4, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b2fc4 {
    unsigned short unk_00;
};

extern struct UnkStruct_020b2fc4 *func_020b3038(int *a, int *b);
extern void *func_0204e414(void);
extern int func_0204e3f4(void *p, int a, int b, int c);
extern int func_0204e404(void *p, unsigned short *s, int a, int b);

void func_020b2fc4(int param)
{
    unsigned short val;
    int a, b;
    struct UnkStruct_020b2fc4 *p;
    void *q;
    int cond, cond2;

    val = (unsigned short) param;
    cond = (val >= 0x5000 && val <= 0x5021);
    if (cond != 0) {
        p = func_020b3038(&a, &b);
        if (p != 0) {
            q = func_0204e414();
            if (q != 0) {
                cond2 = (p->unk_00 >= 0x5000 && p->unk_00 <= 0x5021);
                if (cond2 != 0) {
                    func_0204e3f4(q, a, b, 0);
                }
                func_0204e404(q, &val, a, b);
            }
        }
    }
}
