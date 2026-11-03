/* music_list_scene_4: 4 functions, module ov144
 * mwccarm 1.2/base -O4,s
 * func_ov144_0229b1c4 @ 0x0229b1c4, 0x90 bytes, Thumb
 * func_ov144_0229b130 @ 0x0229b130, 0x94 bytes, Thumb
 * func_ov144_0229b02c @ 0x0229b02c, 0x104 bytes, Thumb, emits _ZN18Obj_ov144_0229b3f819func_ov144_0229b02cEv
 * func_ov144_0229afcc @ 0x0229afcc, 0x60 bytes, Thumb, emits _ZN18Obj_ov144_0229b3f819func_ov144_0229afccEv
 */

#include "cpp/ov144/Obj_ov144_0229b3f8.h"

extern "C" int func_0206fe54(void);
extern "C" void func_ov002_02209eb8(void *);
extern "C" int func_ov144_02299680(void *, int);
extern "C" int func_ov002_02207f60(void *);
extern "C" void func_ov002_0220ad18(void *, int);
extern "C" void func_02088df8(int, void *, int, void *, int, int, int, int, int, int, int, int);

class UnkStruct_0229b1c4_2 {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
};

struct UnkStruct_0229b1c4 {
    char pad_00[0x94];
    void *bufPtr;
    char pad_98[0x0C];
    int count;
    char pad_A8[0x80];
    UnkStruct_0229b1c4_2 obj;
};

extern unsigned char data_ov144_0229b3b0[];
extern "C" void func_ov144_0229ad90(void *obj);
extern "C" void func_ov144_0229ad70(void *obj);

class UnkStruct_0229b130 {
  public:
    char pad_00[0x8c];
    unsigned char idx;
};

typedef void (UnkStruct_0229b130::*PMF)();

extern PMF data_ov144_0229b3a0;
extern PMF data_ov144_0229b3a8;
extern PMF data_ov144_0229b350;
extern PMF data_ov144_0229b398;
extern "C" void func_0206f58c(void);
extern "C" int func_0206f56c(void);
extern "C" void func_ov144_0229a17c(void *obj);
extern "C" void func_ov144_0229a798(void *obj);
extern "C" unsigned char *func_ov002_022080a0(void *obj, unsigned char value);
extern "C" void func_ov144_0229add8(void *obj);
extern "C" void func_ov144_0229add0(void *obj);

extern "C" int func_ov144_0229b1c4(UnkStruct_0229b1c4 *s)
{
    int zero = 0;
    int neg1 = ~zero;
    int one = 1;
    int big = 0x1000;
    void *p4;
    if (func_0206fe54()) {
        func_ov002_02209eb8((char *) s + 0xC4);
    }
    if (!func_ov144_02299680(s, 1)) {
        return 0;
    }
    func_ov002_0220ad18((char *) s + 0x170, func_ov002_02207f60(s));
    p4 = (char *) s->bufPtr + 0x60;
    if (s->count > 0) {
        s->obj.f2();
        func_02088df8(one, (void *) data_ov144_0229b3b0, 0x80, p4, neg1, one, big, big, zero, neg1, zero, zero);
    }
    return 1;
}

extern "C" int func_ov144_0229b130(UnkStruct_0229b130 *obj)
{
    static int initialized = 0;
    static PMF table[4];

    if ((initialized & 1) == 0) {
        table[0] = data_ov144_0229b3a0;
        table[1] = data_ov144_0229b3a8;
        table[2] = data_ov144_0229b350;
        table[3] = data_ov144_0229b398;
        initialized |= 1;
    }

    func_ov144_0229ad90(obj);
    (obj->*table[obj->idx])();
    func_ov144_0229ad70(obj);
    return 1;
}

void Obj_ov144_0229b3f8::func_ov144_0229b02c()
{
    static void (Obj_ov144_0229b3f8::*table[13])() = {
        &Obj_ov144_0229b3f8::func_ov144_0229ab88, &Obj_ov144_0229b3f8::func_ov144_0229ab54,
        &Obj_ov144_0229b3f8::func_ov144_0229ab20, &Obj_ov144_0229b3f8::func_ov144_0229aabc,
        &Obj_ov144_0229b3f8::func_ov144_0229aa70, &Obj_ov144_0229b3f8::func_ov144_0229aa30,
        &Obj_ov144_0229b3f8::func_ov144_0229aa08, &Obj_ov144_0229b3f8::func_ov144_0229a9d4,
        &Obj_ov144_0229b3f8::func_ov144_0229a9b0, &Obj_ov144_0229b3f8::func_ov144_0229a948,
        &Obj_ov144_0229b3f8::func_ov144_0229a894, &Obj_ov144_0229b3f8::func_ov144_0229a868,
        &Obj_ov144_0229b3f8::func_ov144_0229a83c};
    (this->*table[subState])();
}

int Obj_ov144_0229b3f8::func_ov144_0229afcc()
{
    void *obj = (void *) this;
    func_0206f58c();
    if (func_0206f56c() != 0) {
        unsigned char val = ((unsigned char *) obj)[0x8d];
        switch (val) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                func_ov144_0229a17c(obj);
                func_ov144_0229a798(obj);
                func_ov002_022080a0(obj, 1);
                break;
        }
    }
    func_ov144_0229add8(obj);
    ((Obj_ov144_0229b3f8 *) obj)->func_ov144_0229b02c();
    func_ov144_0229add0(obj);
    return 1;
}
