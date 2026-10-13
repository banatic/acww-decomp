/* func_020692c8 @ 0x020692c8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020a8308(void *);
extern void func_0206c224(void *, void *);
extern void func_0206c1a8(void *, unsigned int);

struct UnkStruct_020692c8 {
    char unk_00[0x24];        // 0x00
    void *unk_24;             // 0x24
    void *unk_28;             // 0x28
    char unk_2C[0x38 - 0x2C]; // 0x2C
    char unk_38[0x5c - 0x38]; // 0x38
    unsigned int value_5c;    // 0x5c
};

void func_020692c8(struct UnkStruct_020692c8 *r4)
{
    r4->value_5c = func_020a8308(&r4->unk_38);
    func_0206c224(r4->unk_28, &r4->unk_38);
    func_0206c1a8(r4->unk_28, r4->value_5c);
    *((unsigned int *) ((char *) r4->unk_24 + 0x1a54)) = r4->value_5c;
}
