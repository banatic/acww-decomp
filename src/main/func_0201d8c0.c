/* func_0201d8c0 @ 0x0201d8c0, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x124];
    u16 unk_124;
    u8 pad_126[0x19c - 0x126];
    u16 unk_19C;
} UnkStruct_0201d8c0;

extern int func_020984e8(void);
extern int func_02099734(int a);
extern int func_02098eb8(int id);
extern int func_02098f0c(u16 *p0, u16 *p1, int p2, int p3);
extern int func_020996ac(int a);
extern s32 OSi_DoUnlockByWord__main_0203cd2c(int lockID, void *lockp, void *ctrlFuncp, BOOL b);
extern int func_020154b4(UnkStruct_0201d8c0 *s, u16 *p, unsigned int v2, unsigned char v3, unsigned int v4);

int func_0201d8c0(UnkStruct_0201d8c0 *self)
{
    u16 code = self->unk_124;

    if (self->unk_19C != 0xfff1) {
        code = self->unk_19C;
    }
    if (code == 0xfff1) {
        goto fail;
    }

    {
        int a = func_020984e8();
        int b = func_02099734(a);
        int slotIdx = func_02098eb8(b);

        if (slotIdx == -1) {
            goto fail;
        }

        func_02098f0c((u16 *) b, &code, slotIdx, 0);
        {
            int lockId = func_020996ac(a);
            OSi_DoUnlockByWord__main_0203cd2c(lockId, &code, 0, 1);
        }
        func_020154b4(self, &code, 0, 5, 0);
        return 1;
    }

fail:
    return 0;
}
