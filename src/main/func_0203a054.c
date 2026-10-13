/* func_0203a054 @ 0x0203a054, 0x158 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0203a054 {
    unsigned char pad_00[0xc];
    int unk_0C;
    int unk_10;
    unsigned char pad_14[0x48 - 0x14];
    int unk_48;
    int unk_4C;
    int unk_50;
    unsigned char pad_54[0xb4 - 0x54];
    unsigned char unk_B4;
} UnkStruct_0203a054;

extern int func_0208a1d0(void *p);
extern int func_0208aef0(UnkStruct_0203a054 *s);
extern int func_0208a1b0(void *p, int n);
extern int func_0208aeec(UnkStruct_0203a054 *s);
extern int func_0208a198(void *p, int n);
extern void func_02088df8(int a0, int a1, int a2, int a3, int s1, int s2, int s3, int s4, int s5, int s6, int s7, int s8);

void func_0203a054(UnkStruct_0203a054 *self)
{
    int a, b, s;
    int a2, b2, s2;

    if (self->unk_B4 == 0) {
        return;
    }
    if (self->unk_0C == 0) {
        a = func_0208a1d0((char *) self + 0x30);
        b = func_0208aef0(self) + func_0208a1b0((char *) self + 0x30, -1);
        s = self->unk_50 + (self->unk_4C + (self->unk_48 + func_0208aeec(self)) + func_0208a198((char *) self + 0x30, -1));
        func_02088df8(0, a, b, s, self->unk_10, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    } else {
        a = func_0208a1d0((char *) self + 0x1c);
        b = func_0208aef0(self) + func_0208a1b0((char *) self + 0x1c, -1);
        s = self->unk_50 + (self->unk_4C + (self->unk_48 + func_0208aeec(self)) + func_0208a198((char *) self + 0x1c, -1));
        a2 = func_0208a1d0((char *) self + 0x30);
        b2 = func_0208aef0(self) + func_0208a1b0((char *) self + 0x30, -1);
        s2 = self->unk_50 + (self->unk_4C + (self->unk_48 + func_0208aeec(self)) + func_0208a198((char *) self + 0x30, -1));
        func_02088df8(2, a, b, s, self->unk_10, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        func_02088df8(2, a2, b2, s2, self->unk_10, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}
