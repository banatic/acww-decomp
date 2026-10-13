/* func_0208e0dc @ 0x0208e0dc, 0x66 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208e0dc {
    char c;
};

struct UnkStruct_0208e0dc_2 {
    int unk_00;
    int unk_04;
};

struct UnkStruct_0208e0dc_3;
typedef unsigned int (*InnerFunc)(struct UnkStruct_0208e0dc_3 *);

struct UnkStruct_0208e0dc_3 {
    InnerFunc *funcs;
    char pad_04[0x30 - 4];
    unsigned int unk_30;
};

struct UnkStruct_0208e0dc_4 {
    char pad_00[0x0c];
    void *unk_0C;
    char pad_10[0x14 - 0x10];
    struct UnkStruct_0208e0dc y;
    char pad_after_y[0x34 - (0x14 + sizeof(struct UnkStruct_0208e0dc))];
    int unk_34;
    char pad_after_34[0x6c - (0x34 + 4)];
    struct UnkStruct_0208e0dc_3 *unk_6C;
};

extern struct UnkStruct_0208e0dc_2 *func_0208a1c8(struct UnkStruct_0208e0dc *);
extern void func_0208a1e0(struct UnkStruct_0208e0dc *, int, int);

void func_0208e0dc(struct UnkStruct_0208e0dc_4 *self)
{
    unsigned int r7;
    unsigned int r6;
    int r4;
    int limit;

    if (self->unk_6C == 0) {
        return;
    }
    r7 = self->unk_6C->funcs[3](self->unk_6C);
    r6 = (r7 + 7) >> 3;
    r4 = func_0208a1c8(&self->y)->unk_04 - 1;
    limit = (int) (r6 - 1);
    if (limit < 0) {
        r4 = 0;
    } else if (limit <= r4) {
        r4 = limit;
    }
    func_0208a1e0(&self->y, r4, 0);
    self->unk_6C->unk_30 = ((r6 << 3) - r7) >> 1;
    if (self->unk_0C == 0) {
        self->unk_34 = 0;
    } else {
        self->unk_34 = r4 * -4 + 0x24;
    }
}