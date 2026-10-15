/* func_ov105_0229e860 @ 0x0229e860, 0xac bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov105_0229fad019func_ov105_0229e860Ev
 */

#include "cpp/ov105/Obj_ov105_0229fad0.h"

extern "C" unsigned char data_021fbdd8;
extern "C" int func_ov105_0229c340(unsigned char *self, int a);
extern "C" unsigned char *func_ov002_02208098(unsigned char *self, unsigned char value);
extern "C" void func_ov002_02207ce4(unsigned char *self, int a);
extern "C" int func_ov105_0229d310(unsigned char *self);
extern "C" void func_ov105_0229d970(unsigned char *self, unsigned char a);
extern "C" int func_ov002_02207cc0(int);
extern "C" void func_ov105_0229cadc(unsigned char *self, unsigned char a, int b);
extern "C" void func_ov002_02207d00(unsigned char *self);

void Obj_ov105_0229fad0::func_ov105_0229e860()
{
    unsigned char *self = (unsigned char *) this;
    if (data_021fbdd8 == 0) {
        if (func_ov105_0229c340(self, 4) != 0) {
            func_ov002_02208098(self, 3);
            ((Obj_ov105_0229fad0 *) self)->func_ov105_0229f25c();
        } else {
            func_ov002_02208098(self, 0);
            func_ov002_02207ce4(self + 0x23bc, 0x3c);
        }
    } else {
        if (func_ov105_0229c340(self, 4) != 0) {
            if (func_ov105_0229d310(self) != 0) {
                func_ov105_0229d970(self, self[0x2b5]);
                return;
            } else {
                if (func_ov002_02207cc0((int) (self + 0x23bc)) != 0) {
                    if (self[0x2c3] != 0) {
                        self[0x2c3]--;
                    } else {
                        func_ov105_0229cadc(self, self[0x2b5], 1);
                        func_ov002_02208098(self, 2);
                    }
                    return;
                }
            }
        }
        func_ov002_02207d00(self + 0x23bc);
    }
}
