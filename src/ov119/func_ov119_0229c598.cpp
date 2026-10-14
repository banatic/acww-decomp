/* func_ov119_0229c598 @ 0x0229c598, 0x5a bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov119_0229cea019func_ov119_0229c598Ev
 */

#include "cpp/ov119/Obj_ov119_0229cea0.h"

extern "C" void func_ov119_0229c2a8(void *);
extern "C" void func_ov119_0229c218(void *);
extern "C" void func_ov119_0229c1a0(void *);
extern "C" void func_ov119_0229bb0c(void *);
extern "C" int func_ov002_02209770(void *);
extern "C" int func_0206f52c(int);
extern "C" int func_0206f50c(void);
extern "C" int func_0206fc8c(int);
extern "C" int func_ov119_0229a650(void *, int);
extern "C" void func_ov119_0229a69c(void *, int);
extern "C" void func_ov002_02208090(void *, int);

void Obj_ov119_0229cea0::func_ov119_0229c598()
{
    void *self = (void *) this;
    func_ov119_0229c2a8(self);
    func_ov119_0229c218(self);
    func_ov119_0229c1a0(self);
    func_ov119_0229bb0c(self);
    func_ov119_0229a69c(self, func_ov119_0229a650(self, (func_0206f52c(func_ov002_02209770((char *) self + 0xdc)) != 0)
                                                            ? func_0206fc8c(func_0206f50c())
                                                            : 0));
    func_ov002_02208090(self, 1);
    ((Obj_ov119_0229cea0 *) self)->func_ov119_0229c534();
}
