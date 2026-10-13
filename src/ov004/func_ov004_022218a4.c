/* func_ov004_022218a4 @ 0x022218a4, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Vt Vt;
typedef struct UnkStruct_022218a4 {
    Vt *vt;
} UnkStruct_022218a4;
struct Vt {
    void (*unk_00)(UnkStruct_022218a4 *);
    void (*unk_04)(UnkStruct_022218a4 *);
    void (*unk_08)(UnkStruct_022218a4 *);
};
extern int func_0201c2a4(void *, int);
extern void func_02016108(void *, int);
extern void func_ov004_02221a64(void *, int);
void func_ov004_022218a4(u8 *self, int op)
{
    UnkStruct_022218a4 *s;
    switch (op) {
        case 0:
            s = (UnkStruct_022218a4 *) (self + 0x89c);
            s->vt->unk_08(s);
            func_02016108(self + 0x89c, func_0201c2a4(self, 4));
            func_ov004_02221a64(self, 0);
            break;
        case 8:
            func_ov004_02221a64(self, 2);
            break;
    }
}
