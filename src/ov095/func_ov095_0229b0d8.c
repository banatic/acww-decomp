/* func_ov095_0229b0d8 @ 0x0229b0d8, 0x94 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern void func_020896b8(int, const void *, int, int, int, int, int);
typedef struct {
    int a;
    int b;
} UnkStruct_0229b0d8;
extern UnkStruct_0229b0d8 data_ov095_0229e814[];

struct UnkStruct_0229b0d8_2 {
    char pad_00[0x17];
    unsigned char key;
    unsigned char count;
};

void func_ov095_0229b0d8(struct UnkStruct_0229b0d8_2 *self, int param1, int param2)
{
    int local0 = 0;
    int local1 = 0;
    int local2 = 0;
    int i;
    for (i = 0; i < self->count; i++) {
        int v0 = -1;
        int v1 = param2;
        if (self->key == i) {
            v0 = 0xb;
            v1 = param2 + 2;
        }
        func_020896b8(1, &data_ov095_0229e814[i], param1, v1, -1, 2, local0);
        func_020896b8(1, &data_ov095_0229e814[i + 4], param1, v1, v0, 2, local1);
        func_020896b8(1, &data_ov095_0229e814[i + 8], param1, param2, -1, 2, local2);
    }
}
