/* func_ov003_0220f994 @ 0x0220f994, 0x64 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073908(int a, int b);
extern void func_0204f818(int *out0, int *out1, int *input);
extern void func_ov003_02224384(int a, int *b, int c);

typedef struct {
    int a;
    int b;
    unsigned char pad_08[2];
    unsigned char flag;
} UnkStruct_0220f994_2;

typedef struct {
    char pad_00[0x7D4];
    UnkStruct_0220f994_2 sub;
    char pad_7E0[0x20];
    int unk_800;
} UnkStruct_0220f994;

void func_ov003_0220f994(UnkStruct_0220f994 *self)
{
    int out[2];
    int copy[2];
    int input[3];
    UnkStruct_0220f994_2 *p;
    int a, b;

    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        return;
    }
    p = &self->sub;
    if (p->flag >= 5u) {
        return;
    }
    b = p->b;
    a = p->a;
    input[0] = a;
    input[1] = 0;
    input[2] = b;
    out[0] = 0;
    out[1] = 0;
    func_0204f818(&out[0], &out[1], input);
    copy[0] = out[0];
    copy[1] = out[1];
    func_ov003_02224384(self->unk_800, copy, 2);
}
