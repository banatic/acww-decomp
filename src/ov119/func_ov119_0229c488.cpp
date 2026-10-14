/* func_ov119_0229c488 @ 0x0229c488, 0x4c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov119_0229cea019func_ov119_0229c488Ev
 */

#include "cpp/ov119/Obj_ov119_0229cea0.h"

extern "C" {
void func_ov119_0229b9a4(void *);
void func_ov002_02207f04(void *, int, int, int, int);
void func_ov002_02207e80(void *, int, int, int);
void func_ov002_02208090(void *, int);
int func_ov002_02207f60(void *);
}

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
