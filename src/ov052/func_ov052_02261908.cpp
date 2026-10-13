/* func_ov052_02261908 @ 0x02261908, 0x44 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

class CActor {
  public:
    char pad_00[0x654];
    int unk_654;
};

typedef int (CActor::*CActorPMF)();

struct SElement {
    CActorPMF pmf;
    int pad_08[2];
};

extern SElement data_ov052_02262000[];

extern "C" void func_ov052_02261908(CActor *obj, int index)
{
    int result = 1;
    SElement *e = &data_ov052_02262000[index];
    if (e->pmf != 0) {
        result = (obj->*e->pmf)();
    }
    if (result != 0) {
        obj->unk_654 = index;
    }
}
