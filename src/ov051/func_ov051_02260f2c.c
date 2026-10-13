/* func_ov051_02260f2c @ 0x02260f2c, 0x68 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} UnkStruct_02260f2c;
extern UnkStruct_02260f2c data_ov051_0226175c;
extern UnkStruct_02260f2c data_ov051_02261754;
extern UnkStruct_02260f2c data_ov051_0226174c;
extern int data_ov051_02261b84;
extern UnkStruct_02260f2c data_ov051_02261b90[3];
typedef struct UnkStruct_02260f2c_2 {
    unsigned char pad_00[0xb4];
    UnkStruct_02260f2c v;
} UnkStruct_02260f2c_2;

void func_ov051_02260f2c(UnkStruct_02260f2c_2 *self, int idx)
{
    if ((data_ov051_02261b84 & 1) == 0) {
        data_ov051_02261b90[0] = data_ov051_0226175c;
        data_ov051_02261b90[1] = data_ov051_02261754;
        data_ov051_02261b90[2] = data_ov051_0226174c;
        data_ov051_02261b84 |= 1;
    }
    self->v = data_ov051_02261b90[idx];
}
