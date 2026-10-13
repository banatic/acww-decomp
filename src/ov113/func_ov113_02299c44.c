/* func_ov113_02299c44 @ 0x02299c44, 0x8a bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02299c44 {
    char pad_00[0x9b];
    u8 unk_9B;
} UnkStruct_02299c44;

extern void func_0206fdd4(void *, int, int, int, int, int);
extern void func_ov113_02299d84(UnkStruct_02299c44 *, int);
extern void func_ov113_02299d94(UnkStruct_02299c44 *, int);

void func_ov113_02299c44(UnkStruct_02299c44 *o, int flag)
{
    u8 st = o->unk_9B;
    int a;
    int n;

    switch (st) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (flag) {
                a = 0xe;
            } else {
                a = 0xd;
            }
            n = st * 6 + 4;
            func_0206fdd4((char *) o + 0xa0, n, 0x14, n + 5, 0x16, a);
            func_ov113_02299d94(o, 1);
            break;
        default:
            if (st == 4) {
                if (flag) {
                    func_ov113_02299d94(o, 2);
                } else {
                    func_ov113_02299d84(o, 2);
                }
            } else {
                if (flag) {
                    func_ov113_02299d94(o, 4);
                } else {
                    func_ov113_02299d84(o, 4);
                }
            }
            break;
    }
}
