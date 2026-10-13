/* func_0208fc7c @ 0x0208fc7c, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct GObj {
    int unk_00;
};
struct UnkStruct_0208fc7c {
    struct GObj *unk_00;
    unsigned char pad_04[0x10 - 4];
    int *unk_10;
};
extern struct UnkStruct_0208fc7c data_020d71cc;

extern int func_0208aef0(void *);
extern int func_0208aeec(void *);
extern void func_02088df8(int a0, int a1, int a2, int a3, int s0, int s1, int s2, int s3, int s4, int s5, int s6, int s7);

struct UnkStruct_0208fc7c_2 {
    unsigned char pad_00[0xc];
    int unk_0C;
    unsigned short unk_10;
    unsigned char unk_12;
    unsigned char pad_13[1];
    int unk_14;
    int unk_18;
};

void func_0208fc7c(struct UnkStruct_0208fc7c_2 *self)
{
    int r4, r6, r7, v20;

    if (self->unk_0C == 0) {
        return;
    }

    r4 = self->unk_14 + func_0208aef0(self);
    r6 = self->unk_18 + func_0208aeec(self);

    r7 = data_020d71cc.unk_00->unk_00;
    v20 = *data_020d71cc.unk_10;

    func_02088df8(0, r7, r4, r6, -1, -1, 0x1000, 0x1000, self->unk_10, -1, 0, 0);
    func_02088df8(0, v20, r4, r6, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);

    if (self->unk_12 != 0) {
        func_02088df8(0, r7, r4, r6, -1, -1, 0x1000, 0x1000, self->unk_10, 2, 0, 0);
        func_02088df8(0, v20, r4, r6, -1, -1, 0x1000, 0x1000, 0, 2, 0, 0);
    }
}
