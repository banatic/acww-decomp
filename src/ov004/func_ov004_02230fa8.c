/* func_ov004_02230fa8 @ 0x02230fa8, 0x94 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern u8 data_021c75b8;
extern int func_020b6590(void);
extern int func_020b7e04(void *a, char *b);
extern u8 func_020b65c4(void);
struct UnkStruct_02230fa8 {
    char pad_00[0x68];
    int unk_68;
};
extern struct UnkStruct_02230fa8 *data_020ccf94;
extern int func_0208ff98(void);
extern u8 data_021f6c38;
extern u8 data_021f6c34;
extern int func_020b755c(int h, Vec3 *v, int *id, u8 *kind);
extern void func_ov004_0223121c(void *self, int i);

void func_ov004_02230fa8(char *self)
{
    Vec3 v;
    int id;
    u8 kind;
    int t;

    t = (data_021c75b8 == 2) ? 1 : 0;
    if (t == 0) {
        return;
    }

    func_020b7e04((void *) func_020b6590(), self + 0x374);

    if (func_020b65c4() == 6) {
        if (data_020ccf94->unk_68 != 4) {
            return;
        }
    }
    if (func_0208ff98() == 0) {
        return;
    }

    t = (data_021f6c38 != 0 && data_021f6c34 != 0) ? 1 : 0;
    if (t == 0) {
        return;
    }

    if (func_020b755c(func_020b6590(), &v, &id, &kind) == 0) {
        return;
    }
    if (id != 0xd) {
        return;
    }

    func_ov004_0223121c(self, 10);
}
