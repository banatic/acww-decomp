/* func_ov076_02278d94 @ 0x02278d94, 0x70 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f9d8(void *);
extern int func_020644cc(int);
extern int func_ov076_02278f0c;
extern const unsigned char data_ov076_02279598[][8];
extern const unsigned int data_ov076_02279594[][2];

struct UnkStruct_02278d94 {
    char pad_00[0xb0];
    int unk_B0;
};

struct UnkStruct_02278d94_2 {
    unsigned int unk_00;
    unsigned char unk_04;
};

void func_ov076_02278d94(struct UnkStruct_02278d94 *s, struct UnkStruct_02278d94_2 *out)
{
    if (func_0206f9d8(&func_ov076_02278f0c) != 0) {
        s->unk_B0 = 0;
    } else {
        if (func_020644cc(2) == 0) {
            s->unk_B0 = 1;
        } else {
            s->unk_B0 = 2;
        }
    }
    if (s->unk_B0 >= 0 && s->unk_B0 < 3) {
        out->unk_04 = data_ov076_02279598[s->unk_B0][0];
        out->unk_00 = data_ov076_02279594[s->unk_B0][0];
    }
}
