/* func_02014360 @ 0x02014360, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02014360 {
    u8 pad_00[8];
    u8 unk_08;
    u8 pad_09;
    u8 unk_0A;
    u8 pad_0B[0x559];
    u8 unk_564[0xD0];
    void *ptr;
};

extern char *func_020160d4(void *p);
extern int func_02019e00(char *p);
extern int func_02019de8(char *p);
extern void func_0201462c(struct UnkStruct_02014360 *a, struct UnkStruct_02014360 *b);

void func_02014360(struct UnkStruct_02014360 *a, struct UnkStruct_02014360 *b)
{
    void *p = b->ptr;
    if (p) {
        if (func_020160d4(p) && func_02019e00(func_020160d4(p) + 0x564) == 8 && func_02019de8(func_020160d4(p) + 0x564) == 0) {
            return;
        }
    }
    if (func_02019e00((char *) b->unk_564) == 8 && func_02019de8((char *) b->unk_564) == 0) {
        return;
    }
    func_0201462c(a, b);
    a->unk_0A = 3;
    a->unk_08 = 5;
}
