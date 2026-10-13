/* func_02036788 @ 0x02036788, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02036788 UnkStruct_02036788;
struct UnkStruct_02036788 {
    u8 pad_00[8];
    u8 unk_08;
    u8 pad_09[4];
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
    u8 unk_10;
};

extern int func_02035ae8(int);
extern int func_02035bdc(int);
extern void func_020366c0(UnkStruct_02036788 *);
extern void func_0203665c(UnkStruct_02036788 *);

void func_02036788(UnkStruct_02036788 *s)
{
    int flag;

    if (s->unk_10 != 0) {
        goto end;
    }
    if (s->unk_0D != 0 && func_02035bdc(func_02035ae8(s->unk_0D)) != 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    func_020366c0(s);
    s->unk_08 = 0x3f;
    func_0203665c(s);
    s->unk_0E = flag;
end:
    s->unk_0F = 0;
}
