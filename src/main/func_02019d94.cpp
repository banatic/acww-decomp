/* func_02019d94 @ 0x02019d94, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02019d94;
typedef void (UnkStruct_02019d94::*PMF)(int);
struct Entry {
    PMF pmf;
    char pad_08[0x10];
};
extern Entry data_021c1ad4[];

class UnkStruct_02019d94 {
  public:
    char pad_00[0x14];
    int unk_14;
    char pad_18[0x4];
    int unk_1C;
    Entry *unk_20;
    char pad_24[0x74];
    char unk_98;
};

extern "C" void func_02019d94(UnkStruct_02019d94 *obj, int a, int idx, int val)
{
    obj->unk_1C = idx;
    if (idx < 0 || idx >= 0x16) {
        obj->unk_1C = 0;
    }
    obj->unk_14 = val;
    obj->unk_20 = &data_021c1ad4[obj->unk_1C];
    obj->unk_98 = 0;
    Entry *p = obj->unk_20;
    if (p != 0) {
        (obj->*(p->pmf))(a);
    }
}
