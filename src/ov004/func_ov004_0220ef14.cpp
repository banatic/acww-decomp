/* func_ov004_0220ef14 @ 0x0220ef14, 0x1ec bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Vec {
    int x, y, z;
};
struct Entry {
    int x, z;
};
struct List {
    int words[9];
};
class Actor {
  public:
    virtual void slot0() = 0;
    virtual void slot1() = 0;
    virtual void slot2() = 0;
    virtual void slot3() = 0;
    virtual void slot4() = 0;
    virtual void slot5() = 0;
    virtual void slot6() = 0;
    virtual void slot7() = 0;
    virtual void slot8() = 0;
    virtual void slot9() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void slot19() = 0;
    virtual void slot20() = 0;
    virtual void slot21() = 0;
    virtual void slot22() = 0;
    virtual void slot23() = 0;
    virtual void slot24() = 0;
    virtual void slot25() = 0;
    virtual void slot26() = 0;
    virtual void slot27() = 0;
    virtual void slot28() = 0;
    virtual void slot29() = 0;
    virtual int query() = 0;
};
extern "C" {
extern int func_ov004_0220e5c8(void *);
extern void func_ov004_0220db94(List *), func_ov004_0220db90(List *);
extern void func_ov004_0220f27c(void *, List *, Vec *, int);
extern void func_ov004_0220f218(u16 *, void *, int);
extern int func_020b65c4(void), func_ov004_0223d348(int), func_ov004_0220e5a8(void *);
extern int func_ov004_0220d2b8(void *);
extern Entry *func_ov004_0220db5c(List *, int);
extern u32 func_ov004_0220db68(List *);
extern void func_020523e4(int, int, int, int, int, int, int, u16 *, int);
extern void *func_ov004_0223cd50(void);
extern void func_ov004_0223ccc4(void *, void *, int, int, int);
extern u16 func_ov004_0220e808(void *, Vec *, int);
extern int func_0203efbc(void *);
extern void func_0203efb0(void *, int);
extern void __register_global_object(void *, void (*)(void *), void *), func_020012dc(void *);
extern void MTX_MultVec43(Vec *, void *, Vec *);
extern short func_020e8ed8(int, int);
extern u32 data_ov004_02256c50, data_ov004_02256c88;
extern Vec data_ov004_02256cb4, data_ov004_02256cd8;
extern u8 data_ov004_02256ca8[], data_ov004_02256ccc[], data_021fbe48[];
}
extern "C" void func_ov004_0220ef14(Actor *actor, int unused, Vec *param, int turn, u8 update)
{
    u8 *self = (u8 *) actor;
    u16 items[3];
    List list;
    Vec origin, forward;
    int option, kind;
    u32 i;
    if (func_ov004_0220e5c8(self)) {
        return;
    }
    func_ov004_0220db94(&list);
    func_ov004_0220f27c(self, &list, param, turn);
    items[0] = 0xfff1;
    if (self[0x288] == 1) {
        if (!(data_ov004_02256c50 & 1)) {
            data_ov004_02256cb4.x = 0;
            data_ov004_02256cb4.y = 0;
            data_ov004_02256cb4.z = 0;
            __register_global_object(&data_ov004_02256cb4, func_020012dc, data_ov004_02256ca8);
            data_ov004_02256c50 |= 1;
        }
        if (!(data_ov004_02256c88 & 1)) {
            data_ov004_02256cd8.x = 0;
            data_ov004_02256cd8.y = 0;
            data_ov004_02256cd8.z = 0x1000;
            __register_global_object(&data_ov004_02256cd8, func_020012dc, data_ov004_02256ccc);
            data_ov004_02256c88 |= 1;
        }
        MTX_MultVec43(&data_ov004_02256cb4, data_021fbe48, &origin);
        MTX_MultVec43(&data_ov004_02256cd8, data_021fbe48, &forward);
        func_ov004_0220f218(&items[1], self, func_020e8ed8(forward.x - origin.x, forward.z - origin.z));
        items[0] = items[1];
    } else {
        func_ov004_0220f218(&items[2], self, (short) (*(short *) (self + 0x8e) + turn));
        items[0] = items[2];
    }
    func_ov004_0223d348(func_020b65c4());
    option = self[0x289] == 0 ? 0 : func_ov004_0220e5a8(self);
    kind = actor->query();
    for (i = 0; i < func_ov004_0220db68(&list); i++) {
        if (i == 0) {
            int flag = func_ov004_0220d2b8(self + 0x740);
            int mode = func_020b65c4();
            Entry *a = func_ov004_0220db5c(&list, i);
            Entry *b = func_ov004_0220db5c(&list, i);
            func_020523e4(mode, a->x, b->z, self[0x288], flag, option, kind, &items[0], 1);
        }
        {
            void *context = func_ov004_0223cd50();
            Entry *a = func_ov004_0220db5c(&list, i);
            Entry *b = func_ov004_0220db5c(&list, i);
            func_ov004_0223ccc4(context, self, a->x, b->z, self[0x288]);
        }
    }
    if (update) {
        u16 value = func_ov004_0220e808(self, param, turn);
        if (value != func_0203efbc(self)) {
            func_0203efb0(self, value);
        }
    }
    func_ov004_0220db90(&list);
}
