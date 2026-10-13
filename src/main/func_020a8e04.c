/* func_020a8e04 @ 0x020a8e04, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020a8e04_2 UnkStruct_020a8e04_2;
typedef struct UnkStruct_020a8e04 {
    char pad_00[0x10];
    int unk_10;
    int unk_14;
    char pad_18[0x64];
    int unk_7C;
    UnkStruct_020a8e04_2 *unk_80;
} UnkStruct_020a8e04;

extern UnkStruct_020a8e04_2 data_021f44dc;
extern void func_020a9228(UnkStruct_020a8e04_2 *p, UnkStruct_020a8e04 *s);
extern void func_020a94a4(UnkStruct_020a8e04_2 *p);
extern void func_020a9354(UnkStruct_020a8e04_2 *p, int n);
extern void func_020a922c(UnkStruct_020a8e04_2 *p, int n);
extern void func_020a9220(UnkStruct_020a8e04_2 *p);

void func_020a8e04(UnkStruct_020a8e04 *self)
{
    UnkStruct_020a8e04_2 *ptr = self->unk_80;
    if (!ptr) {
        ptr = &data_021f44dc;
    }
    self->unk_7C = 1;
    func_020a9228(ptr, self);
    func_020a94a4(ptr);
    func_020a9354(ptr, self->unk_10);
    func_020a922c(ptr, self->unk_14);
    func_020a9220(ptr);
    self->unk_7C = 0;
}
