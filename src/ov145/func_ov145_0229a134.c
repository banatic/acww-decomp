/* func_ov145_0229a134 @ 0x0229a134, 0x28 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208ea70(void *a, int b, int c);

typedef struct {
    char pad_00[0x94];
    int unk_94;
    char pad_98[0x10];
    int unk_A8;
    char pad_AC[0x80];
    char unk_12C;
} struct_ov145_0229a134;

void func_ov145_0229a134(struct_ov145_0229a134 *p)
{
    func_0208ea70(&p->unk_12C, 0x63, p->unk_94 + (p->unk_A8 - 0x4b));
}
