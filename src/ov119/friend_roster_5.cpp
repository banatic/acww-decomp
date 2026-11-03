/* friend_roster_5: 2 functions, module ov119
 * mwccarm 1.2/base -O4,s
 * func_ov119_0229c488 @ 0x0229c488, 0x4c bytes, Thumb, emits _ZN18Obj_ov119_0229cea019func_ov119_0229c488Ev
 * func_ov119_0229c434 @ 0x0229c434, 0x54 bytes, Thumb, emits _ZN18Obj_ov119_0229cea019func_ov119_0229c434Ev
 */

#include "cpp/ov119/Obj_ov119_0229cea0.h"

extern "C" {
void func_ov119_0229b9a4(void *);
void func_ov002_02207f04(void *, int, int, int, int);
void func_ov002_02207e80(void *, int, int, int);
void func_ov002_02208090(void *, int);
int func_ov002_02207f60(void *);
}

extern "C" int func_ov002_02207f3c(void *p, int x);
extern "C" void func_020027f0(int x);
extern "C" void func_ov119_0229a400(void *p, int x);
extern "C" unsigned char *func_ov002_022080a0(void *p, unsigned char value);

struct Type {
    char pad_00[0x94];
    int unk_94;
};

void Obj_ov119_0229cea0::func_ov119_0229c488()
{
    void *r4 = this;
    int result;

    func_ov119_0229b9a4(r4);
    func_ov002_02207f04(r4, 10, 0, 0, 0x30);
    func_ov002_02207e80(r4, 6, 0, 0);
    func_ov002_02207e80(r4, 4, 0, 0);
    func_ov002_02208090(r4, 4);
    result = func_ov002_02207f60(r4);
    r4 = (char *) r4 + 0x94;
    *(int *) r4 = result;
}

void Obj_ov119_0229cea0::func_ov119_0229c434()
{
    struct Type *p = (struct Type *) this;
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov119_0229a400(p, 1);
        func_ov002_022080a0(p, 5);
    } else {
        func_ov002_02207e80(p, 6, 0, 0);
        func_ov002_02207e80(p, 4, 0, 0);
        p->unk_94 = func_ov002_02207f60(p);
    }
}
