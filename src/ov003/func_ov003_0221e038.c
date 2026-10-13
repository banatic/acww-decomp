/* func_ov003_0221e038 @ 0x0221e038, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055124(void *ptr);
extern void func_02056ffc(void *ptr);
extern int func_ov003_0221e6a0(void *ptr);
extern int func_02056f94(void *ptr);
extern void func_020b2800(void *ptr, int val);

typedef struct {
    char pad_00[0x13c];
    int unk_13C;
    char pad_140[0x1d8 - 0x13c - 4];
    int unk_1D8;
    char pad_1DC[0x2b8 - 0x1d8 - 4];
    int unk_2B8;
    char pad_2BC[0x2c0 - 0x2b8 - 4];
    int unk_2C0;
    char pad_2C4[0x2d0 - 0x2c0 - 4];
    int *unk_2D0;
} struct_0221e038;

void func_ov003_0221e038(struct_0221e038 *s)
{
    func_02055124(&s->unk_13C);
    func_02056ffc(&s->unk_2B8);
    *s->unk_2D0 = s->unk_2C0;
    if (func_ov003_0221e6a0(s) != 0) {
        if (func_02056f94(&s->unk_1D8) != 0) {
            func_020b2800(s, 4);
        }
    }
}
