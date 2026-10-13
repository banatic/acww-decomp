/* func_ov003_0221fec0 @ 0x0221fec0, 0xc0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 unk_00;
    u32 arr[5];
    u32 unk_18;
    u8 unk_1C;
} UnkStruct_0221fec0;

extern void func_ov003_0221ff80(UnkStruct_0221fec0 *s);
extern int func_0204cb90(const void *a, int b);
extern int func_02064b2c(const void *a, int b, int c, int _x);
extern int NNS_FndMountArchive(void *out, const void *src, int x);
extern void func_02064328(const void *a, const void *b, unsigned int c);
extern void *NNS_FndGetArchiveFileByName(const void *p);
extern void *func_02107828(void *p);
extern u32 func_021077e8(void *p);
extern void *NNS_G3dGetTexPatAnmSet(void *p);
extern u32 func_02107bf8(void *p, int x);
extern void func_0210285c(void *p);
extern void func_02056064(void *p, int x);
extern int data_021c9b1c;
extern char data_021f39fc[];
extern char data_ov003_02239b94[];
extern char data_ov003_02239ba4[];
extern char data_ov003_02239ba8[];
extern char data_ov003_02239bc4[];
extern char data_ov003_02239be0[];
extern char data_ov003_0223cec8[];

int func_ov003_0221fec0(UnkStruct_0221fec0 *s)
{
    u8 buf[0x6c];
    unsigned int i;
    int ret;

    func_ov003_0221ff80(s);

    if (func_0204cb90(data_021f39fc, 0x11) == -1) {
        return 0;
    }

    ret = func_02064b2c(data_ov003_02239b94, data_021c9b1c, 4, 0);

    if (NNS_FndMountArchive(buf, data_ov003_02239ba4, ret) != 0) {
        for (i = 0; i < 5; i++) {
            char *p;
            u16 a;
            u32 b;

            func_02064328(data_ov003_0223cec8, data_ov003_02239ba8, i);
            p = (char *) func_02107828(NNS_FndGetArchiveFileByName(data_ov003_0223cec8));
            a = *(u16 *) (p + 0xe);
            b = *(u32 *) (p + a + 0xc);
            s->arr[i] = (u32) (p + b);
        }

        s->unk_00 = func_021077e8(NNS_FndGetArchiveFileByName(data_ov003_02239bc4));
        func_02056064((void *) s->unk_00, 0);

        s->unk_18 = func_02107bf8(NNS_G3dGetTexPatAnmSet(NNS_FndGetArchiveFileByName(data_ov003_02239be0)), 0);
        s->unk_1C = 1;
        func_0210285c(buf);
    }

    return 1;
}