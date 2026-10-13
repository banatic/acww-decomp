/* func_020a9164 @ 0x020a9164, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a9164 {
    char pad_00[4];
    int unk_04;
    char pad_08[0x1c];
    int unk_24;
    char pad_28[4];
    int unk_2C;
};

extern void func_020a8e8c(int);
extern void func_020a9318(struct UnkStruct_020a9164 *);

void func_020a9164(struct UnkStruct_020a9164 *p)
{
    if (p->unk_24) {
        func_020a8e8c(p->unk_24);
    }
    if (p->unk_2C && p->unk_04 == p->unk_2C) {
        p->unk_2C = 0;
        func_020a9318(p);
    }
}
