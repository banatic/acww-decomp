/* func_02058280 @ 0x02058280, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x6C];
    int unk_6C;
    int unk_70;
    int unk_74;
    int unk_78;
    int unk_7C;
    int unk_80;
    int unk_84;
    int unk_88;
    int unk_8C;
    int unk_90;
    int unk_94;
    int unk_98;
    char pad_9C[0x38];
    char unk_D4;
    short unk_D6;
} UnkStruct_02058280;

extern int data_021c9390[3];
extern int _s32_div_f(int, int);
extern void func_02059674(UnkStruct_02058280 *, int);

void func_02058280(UnkStruct_02058280 *obj)
{
    int b, a, c;

    obj->unk_6C = 0;
    obj->unk_70 = 0;
    obj->unk_74 = 0;

    obj->unk_84 = data_021c9390[0];
    obj->unk_88 = data_021c9390[1];
    obj->unk_8C = data_021c9390[2];

    obj->unk_78 = 0;
    obj->unk_7C = 0;
    obj->unk_80 = 0;

    a = _s32_div_f(obj->unk_8C, 8);
    if (a < 0) {
        a = -a;
    }

    b = _s32_div_f(obj->unk_88, 8);
    if (b < 0) {
        b = -b;
    }

    c = _s32_div_f(obj->unk_84, 8);
    if (c < 0) {
        c = -c;
    }

    obj->unk_90 = c;
    obj->unk_94 = b;
    obj->unk_98 = a;

    func_02059674(obj, 1);

    obj->unk_D6 = 0;
    obj->unk_D4 = 0;
}
