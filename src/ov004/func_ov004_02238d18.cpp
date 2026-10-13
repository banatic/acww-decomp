/* func_ov004_02238d18 @ 0x02238d18, 0x70 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02238d18 {
    int a;
    ~UnkStruct_02238d18() {}
};
#define F(k) (*(int *) (self + k))
extern "C" void func_ov004_02238d18(char *self)
{
    UnkStruct_02238d18 t;
    F(0x258) = 0x1000 - F(0x278) * F(0x268);
    if (F(0x258) < F(0x27c)) {
        F(0x258) = F(0x27c);
        F(0x25c) = F(0x27c);
        F(0x260) = F(0x27c);
        *(u8 *) (self + 0x264) = 0;
        F(0x268) = 0;
    } else {
        F(0x25c) = F(0x258);
        F(0x260) = F(0x258);
    }
}
