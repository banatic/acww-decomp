/* func_ov145_02299a34 @ 0x02299a34, 0x78 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x9c];
    int A;
    int B;
} UnkStruct_02299a34;

extern void func_ov145_02299b94(UnkStruct_02299a34 *p, int a);
extern void func_ov145_0229a0d0(UnkStruct_02299a34 *p);

void func_ov145_02299a34(UnkStruct_02299a34 *p)
{
    if (p->A == p->B) {
        return;
    }
    if (p->A > p->B) {
        p->A = p->A - 4;
        if (p->A < p->B) {
            p->A = p->B;
        }
    } else {
        p->A = p->A + 4;
        if (p->A > p->B) {
            p->A = p->B;
        }
    }
    func_ov145_02299b94(p, p->A);
    func_ov145_0229a0d0(p);
}
