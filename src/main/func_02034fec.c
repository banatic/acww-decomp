/* func_02034fec @ 0x02034fec, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035fec(void *p, int value);
typedef struct {
    int a;
    int b;
} Pair;
extern Pair data_020da26c;
extern void func_02034e28(void *self, Pair p);

typedef struct {
    char pad_00[4];
    unsigned short unk_04;
    char pad_06[12];
    unsigned char unk_12;
    unsigned char unk_13;
    unsigned char unk_14;
    char pad_15[0x1c0 - 0x15];
    int unk_1C0;
    char pad_1C4[0x2b4 - 0x1c4];
    char unk_2B4;
} UnkStruct_02034fec;

void func_02034fec(UnkStruct_02034fec *self)
{
    if (self->unk_1C0 <= 0) {
        return;
    }
    if (self->unk_12 != 0) {
        return;
    }
    if (self->unk_04 != 0xffff) {
        func_02035fec(&self->unk_2B4, self->unk_04);
        self->unk_14 = 1;
    }
    func_02034e28(self, data_020da26c);
    self->unk_12 = 1;
}
