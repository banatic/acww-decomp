/* func_0208ea98 @ 0x0208ea98, 0x120 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xc];
    int unk_0C;
    int unk_10;
    unsigned char sub1[0x14];
    unsigned char sub2[0x14];
    int unk_3C;
    unsigned char unk_40;
    unsigned char pad_41[3];
    int unk_44;
} UnkStruct_0208ea98;

extern int func_0208a1d0(void *sub);
extern int func_0208a1b0(void *sub, int flag);
extern int func_0208a198(void *sub, int flag);
extern int func_0208aef0(UnkStruct_0208ea98 *self);
extern int func_0208aeec(UnkStruct_0208ea98 *self);
extern void func_02088df8(int mode, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11);

void func_0208ea98(UnkStruct_0208ea98 *self)
{
    if (self->unk_3C == 0) {
        return;
    }

    {
        int A = func_0208a1d0(self->sub1);
        int B = func_0208a1d0(self->sub2);
        int C = func_0208a1b0(self->sub1, -1);
        int D = func_0208a198(self->sub1, -1);
        int E = func_0208a1b0(self->sub2, -1);
        int F = func_0208a198(self->sub2, -1);
        int baseX = self->unk_0C + func_0208aef0(self);
        int baseY = self->unk_10 + func_0208aeec(self);

        if (self->unk_40) {
            func_02088df8(0, A, baseX + C, baseY + D, -1, self->unk_44, 0x1000, 0x1000, 0, -1, 0, 0);
            func_02088df8(0, B, baseX + E, baseY + F, -1, self->unk_44, 0x1000, 0x1000, 0, -1, 0, 0);
        } else {
            func_02088df8(1, A, baseX + C, baseY + D, -1, self->unk_44, 0x1000, 0x1000, 0, -1, 0, 0);
            func_02088df8(1, B, baseX + E, baseY + F, -1, self->unk_44, 0x1000, 0x1000, 0, -1, 0, 0);
        }
    }
}
