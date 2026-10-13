/* func_ov130_02299c08 @ 0x02299c08, 0x140 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[7];
    u8 unk_07;
    u8 unk_08;
    char pad_09[3];
    int unk_0C;
    char pad_10[4];
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
} UnkStruct_02299c08;

extern void func_ov130_02299ac0(UnkStruct_02299c08 *s, int a, void *p, char *q, int k);
extern void func_ov130_02299a58(UnkStruct_02299c08 *s, int a, void *p, char *q, int k);
extern void func_ov130_02299b88(UnkStruct_02299c08 *s, int a, void *p, char *q, int k);
extern void func_ov130_02299bd8(UnkStruct_02299c08 *s, int a, void *p, char *q, int k);

extern void *data_ov130_0229a870[];
extern char *data_ov130_0229a858[];

void func_ov130_02299c08(UnkStruct_02299c08 *s)
{
    void *a;
    char *b;
    int v;

    a = data_ov130_0229a870[s->unk_08];
    b = data_ov130_0229a858[s->unk_08];

    switch (s->unk_08) {
        case 4:
            if (s->unk_0C == 0) {
                func_ov130_02299ac0(s, 0xa, a, b, 2);
            } else {
                func_ov130_02299a58(s, s->unk_0C, a, b, 2);
            }
            break;
        case 5:
            if (s->unk_0C == 0) {
                func_ov130_02299a58(s, 0, a, b, 9);
                func_ov130_02299ac0(s, 0xa, a, b, 7);
            } else {
                func_ov130_02299a58(s, s->unk_0C, a, b, 7);
            }
            break;
        default:
            s->unk_1C = s->unk_14;
            if (s->unk_08 >= 2) {
                func_ov130_02299a58(s, s->unk_1C, a, b, 9);
            } else {
                func_ov130_02299b88(s, s->unk_1C, a, b, 6);
            }
            if (s->unk_0C == 0) {
                if (s->unk_08 >= 2) {
                    func_ov130_02299ac0(s, 0xa, a, b + 3, 9);
                } else {
                    func_ov130_02299bd8(s, 0xa, a, b + 3, 6);
                }
            } else {
                if (s->unk_08 >= 2) {
                    func_ov130_02299a58(s, s->unk_0C, a, b + 3, 9);
                } else {
                    func_ov130_02299b88(s, s->unk_0C, a, b + 3, 6);
                }
            }
            if (s->unk_08 == 0 || s->unk_08 == 2) {
                v = s->unk_18;
                if (s->unk_07 != 0) {
                    v = v + s->unk_0C;
                }
                s->unk_20 = v;
                if (s->unk_08 >= 2) {
                    func_ov130_02299a58(s, s->unk_20, a, b + 6, 9);
                } else {
                    func_ov130_02299b88(s, s->unk_20, a, b + 6, 6);
                }
            }
            break;
    }
}
