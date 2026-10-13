/* func_02065e60 @ 0x02065e60, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020984e8(void);
extern void func_02099734(void);
extern unsigned char *func_02098ddc(void);
extern void func_02051c08(void *dest, const void *src, int size);

struct UnkStruct_02065e60 {
    unsigned char pad_00[0x22];
    unsigned char unk_22;
    unsigned char pad_23[0x44 - 0x23];
    unsigned char unk_44[0xA];
    unsigned char pad_4E[0xF8 - 0x4E];
    unsigned char unk_F8;
};

void func_02065e60(struct UnkStruct_02065e60 *p)
{
    unsigned char *result;

    if ((unsigned char) (p->unk_22 + 0xfe) <= 1) {
        return;
    }

    func_020984e8();
    func_02099734();
    result = func_02098ddc();
    func_02051c08(result, p->unk_44, 0xa);
    p->unk_F8 = result[0x48];
}
