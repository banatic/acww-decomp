/* func_02016448 @ 0x02016448, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0201af24(void *);
extern int FX_MulFunc(int, int);

struct UnkStruct_02016448 {
    char pad_00[8];
    int unk_08;
    char pad1[8];
    int unk_14;
};

struct Other {
    char pad_00[0x98];
    int unk_98;
    char pad1[0x18c - 0x98 - 4];
    int unk_18C;
    char pad_190[0x198 - 0x18c - 4];
    int unk_198;
};

void func_02016448(struct UnkStruct_02016448 *self, struct Other *other)
{
    int *p = &other->unk_98;
    int f = *p;
    if (f == 0) {
        self->unk_08 = 0x1000;
    } else {
        if (*(int *) func_0201af24((char *) other + 0x350) == 0) {
            self->unk_08 = 0x1000;
        } else {
            self->unk_08 = FX_MulFunc(f, self->unk_14);
        }
    }
    if (self->unk_08 <= other->unk_18C) {
        other->unk_198 = self->unk_08;
    }
}
