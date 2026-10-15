/* func_02023ac0 @ 0x02023ac0, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02023ac0_2 {
    u8 pad_00[0x830];
    void *unk_830;
} UnkStruct_02023ac0_2;

typedef struct UnkStruct_02023ac0 {
    u8 pad_00[0x100];              // 0x000
    UnkStruct_02023ac0_2 *unk_100; // 0x100
    u8 unk_104[0x1e];              // 0x104
    u8 unk_122;                    // 0x122
    u8 pad_123[0x79];              // 0x123 - 0x19b
    u16 unk_19C;                   // 0x19c
} UnkStruct_02023ac0;

typedef struct UnkStruct_02023ac0_3 {
    void *ptr; // 0x00
    u8 byte;   // 0x04
} UnkStruct_02023ac0_3;

extern int func_020984e8(void);
extern void func_0202d5e4(void *buf, int val);
extern void func_02015de4(void *a, void *b, int c, int d);
extern unsigned int func_0208150c(void *p);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);

extern struct {
    u32 a;
    u8 b;
} data_020c8c00;

void func_02023ac0(UnkStruct_02023ac0 *self, UnkStruct_02023ac0_3 *out)
{
    u16 buf[2];
    int ret;

    func_0202d5e4(buf, func_020984e8());
    self->unk_19C = buf[0];

    if (self->unk_19C == 0xFFF1) {
        func_0202d5e4(buf + 1, 0);
        self->unk_19C = buf[1];
    }

    if (self->unk_19C != 0xFFF1) {
        func_02015de4(self, &self->unk_19C, 1, 7);
    }

    ret = func_020036e8((unsigned char *) func_0208150c(self->unk_100->unk_830));

    func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, ret, data_020c8c00.a, data_020c8c00.b, 0, 0);

    out->ptr = self->unk_104;
    out->byte = self->unk_122;
}
