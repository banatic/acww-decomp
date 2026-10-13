/* func_ov004_0220cb68 @ 0x0220cb68, 0xc0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} UnkStruct_0220cb68;

typedef struct {
    unsigned char pad_00[0x150];
    int unk_150;
    int unk_154;
    int unk_158;
    int unk_15C;
    short unk_160;
    short unk_162;
    short unk_164;
    unsigned char pad_166[2];
    int unk_168;
    unsigned char pad_16C[0x284 - 0x16c];
    int unk_284;
    unsigned char unk_288;
} RoomObject;

extern int func_020961a8(int k);
extern void func_ov004_0220fefc_unk(RoomObject *self, UnkStruct_0220cb68 *out);
extern int func_ov004_0223c5a4_unk(UnkStruct_0220cb68 *v);
extern short func_0204bc50(int a, int b);
extern int func_ov004_02233ba8_unk(short *h, UnkStruct_0220cb68 *v);

int func_ov004_0220cb68(RoomObject *self)
{
    self->unk_15C = 0x555;
    self->unk_150 = 0;
    self->unk_154 = 0;
    self->unk_158 = 0;
    self->unk_160 = 0;
    self->unk_162 = 0;
    self->unk_164 = 0x2710;
    self->unk_168 = 0x800;

    if (func_020961a8(4)) {
        UnkStruct_0220cb68 local;
        UnkStruct_0220cb68 local3;
        short h;

        func_ov004_0220fefc_unk(self, &local);

        if (self->unk_288 == 0) {
            local.y = 0;
        } else {
            local.y = func_ov004_0223c5a4_unk(&local);
        }
        local.y = local.y + 0x800;

        h = func_0204bc50(self->unk_284, 0);

        local3.x = local.x;
        local3.y = local.y;
        local3.z = local.z;

        return func_ov004_02233ba8_unk(&h, &local3);
    }
    return 1;
}
