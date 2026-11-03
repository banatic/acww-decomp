/* missing_npc2_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020c36d4 @ 0x020c36d4, 0x8c bytes, Thumb
 * func_020c3690 @ 0x020c3690, 0x44 bytes, Thumb
 */

class CObj {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
};

extern "C" int func_0201c2a4(void *self, int value);
extern "C" void func_02016108(void *obj, int value);

class UnkStruct_020c3690 {
  public:
    int method();
    char pad_00[0x654];
    int unk_654;
};

struct Entry {
    int (UnkStruct_020c3690::*pmf)();
    int pad_08;
    int pad_0C;
};

extern Entry data_021fbcd8[];

extern "C" {
void func_020c3690(UnkStruct_020c3690 *obj, int index);
}

extern "C" void func_020c36d4(void *p, int index)
{
    switch (index) {
        case 1:
            ((CObj *) ((char *) p + 0x658))->m2();
            func_02016108((char *) p + 0x658, func_0201c2a4(p, 4));
            func_020c3690((UnkStruct_020c3690 *) p, 1);
            break;
        case 0:
            func_020c3690((UnkStruct_020c3690 *) p, 1);
            break;
        case 3:
            ((CObj *) ((char *) p + 0x658))->m2();
            func_02016108((char *) p + 0x658, func_0201c2a4(p, 4));
            func_020c3690((UnkStruct_020c3690 *) p, 9);
            break;
        case 8:
            func_020c3690((UnkStruct_020c3690 *) p, 0);
            break;
        case 2:
        case 4:
        case 5:
        case 6:
        case 7:
            break;
    }
}

extern "C" void func_020c3690(UnkStruct_020c3690 *obj, int index)
{
    int cond = 1;
    if (data_021fbcd8[index].pmf != 0) {
        cond = (obj->*data_021fbcd8[index].pmf)();
    }
    if (cond != 0) {
        obj->unk_654 = index;
    }
}
