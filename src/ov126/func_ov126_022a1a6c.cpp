/* func_ov126_022a1a6c @ 0x022a1a6c, 0xe0 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov126_022a20c819func_ov126_022a1a6cEv
 */

#include "cpp/ov126/Obj_ov126_022a20c8.h"

extern "C" void func_0206f58c(void);
extern "C" int func_0206f56c(void);
extern "C" int func_0206fca4(void);
extern "C" void func_ov126_0229f7a8(void *, int);
extern "C" int func_ov126_0229ffdc(void *);
extern "C" int func_020ee45c(void *);
extern "C" void func_ov090_022993cc(int, int);
extern "C" void func_ov126_0229f7b8(void *, int);
extern "C" void func_ov002_02207f04(void *, int, int, int, int);
extern "C" void func_ov126_022a16ac(void *);
extern "C" void func_ov002_02208090(void *, int);
extern "C" unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern "C" int func_ov126_0229fc54(void *);
extern "C" void func_02077c40(int);
extern "C" void func_ov126_022a1480(void *);
extern "C" void func_ov126_022a1478(void *);

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
} UnkStruct_022a1a6c;

int Obj_ov126_022a20c8::func_ov126_022a1a6c()
{
    UnkStruct_022a1a6c *self = (UnkStruct_022a1a6c *) this;
    int v;
    int r5;

    v = ((void) (func_0206f58c()), func_0206f56c());
    if (v == 0) {
        goto exit;
    }

    r5 = func_0206fca4();

    switch (r5) {
        case 0x18:
        case 0x19:
        case 0x1a:
        case 0x1b:
            switch (self->unk_8D) {
                case 0:
                case 1:
                case 2:
                case 4:
                case 6:
                case 7:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                    func_ov126_0229f7a8(self, 2);
                    func_ov126_0229ffdc(self);
                    func_ov090_022993cc(func_020ee45c(self), 7);
                    func_ov126_0229f7b8(self, 0x40);
                    func_ov002_02207f04(self, 10, 0, 0, 0x30);
                    func_ov126_022a16ac(self);
                    func_ov002_02208090(self, 5);
                    func_ov002_022080a0((void *) (self), 1);
                    if (r5 == 0x19 || r5 == 0x1b) {
                        func_02077c40(func_ov126_0229fc54(self));
                    }
                    break;
                case 3:
                case 5:
                case 8:
                    break;
            }
            break;
    }

exit:
    func_ov126_022a1480(self);
    ((Obj_ov126_022a20c8 *) self)->func_ov126_022a1b4c();
    func_ov126_022a1478(self);
    return 1;
}
