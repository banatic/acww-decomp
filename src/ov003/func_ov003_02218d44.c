/* func_ov003_02218d44 @ 0x02218d44, 0x88 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02218d44 UnkStruct_02218d44;
typedef struct UnkStruct_02218d44_2 UnkStruct_02218d44_2;

struct UnkStruct_02218d44_2 {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
};

struct UnkStruct_02218d44 {
    unsigned char pad_00[0x7d4];
    UnkStruct_02218d44_2 sub;
    unsigned char pad_7D7[0x19];
    unsigned int unk_7F0;
    unsigned char pad_7F4[8];
    unsigned int unk_7FC;
    unsigned int unk_800;
};

extern unsigned int data_020ccf94;
extern int func_02073908(unsigned int, unsigned int);
extern unsigned int func_02008258(UnkStruct_02218d44 *, unsigned int);
extern int func_ov003_02218ca8(UnkStruct_02218d44 *, void *, int, int);
extern int func_0200d4e8(UnkStruct_02218d44 *, int, int, int);

void func_ov003_02218d44(UnkStruct_02218d44 *s)
{
    unsigned int tmp[2];

    if (func_02073908(data_020ccf94, s->unk_800) == 0) {
        s->unk_7FC = func_02008258(s, s->unk_7F0);
    }

    {
        UnkStruct_02218d44_2 *sub = &s->sub;
        switch (sub->unk_02) {
            case 0:
                break;
            case 1: {
                unsigned int v1 = sub->unk_01;
                unsigned int v0 = sub->unk_00;
                tmp[0] = v0;
                tmp[1] = v1;
                func_ov003_02218ca8(s, tmp, 6, -1);
                break;
            }
            case 2:
                s->unk_7FC = func_02008258(s, s->unk_7F0);
                func_0200d4e8(s, 3, 1, -1);
                break;
        }
    }
}
