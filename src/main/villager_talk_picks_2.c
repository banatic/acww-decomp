/* villager_talk_picks_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202669c @ 0x0202669c, 0x3c bytes, Thumb
 * func_0202664c @ 0x0202664c, 0x50 bytes, Thumb
 * func_020265fc @ 0x020265fc, 0x50 bytes, Thumb
 * func_020265c0 @ 0x020265c0, 0x3c bytes, Thumb
 */

typedef struct {
    char pad_00[3];
    unsigned char unk_03;
    unsigned char unk_04;
} SrcType;

struct UnkStruct_0202664c {
    unsigned char pad_00[3];
    unsigned char unk_03;
    unsigned char unk_04;
};

typedef struct {
    char pad_00[3];
    unsigned char unk_03;
    unsigned char unk_04;
} UnkStruct_020265fc;

extern int func_0202cbdc(void *, int, int, unsigned char, unsigned char);

void func_0202669c(unsigned short *dst, const SrcType *src)
{
    int result;

    *dst = 0xfff1;
    result = func_0202cbdc(dst, 0, 1, src->unk_04, src->unk_03);
    if (result != 0) {
        return;
    }
    func_0202cbdc(dst, 2, 4, src->unk_04, src->unk_03);
}

void func_0202664c(unsigned short *out, struct UnkStruct_0202664c *in)
{
    *out = 0xfff1;
    if (func_0202cbdc(out, 1, 2, in->unk_04, in->unk_03) != 0) {
        return;
    }
    if (func_0202cbdc(out, 0, 0, in->unk_04, in->unk_03) != 0) {
        return;
    }
    func_0202cbdc(out, 3, 4, in->unk_04, in->unk_03);
}

void func_020265fc(unsigned short *param0, UnkStruct_020265fc *param1)
{
    int result;
    *param0 = 0xfff1;
    result = func_0202cbdc((void *) param0, 2, 3, param1->unk_04, param1->unk_03);
    if (result != 0) {
        return;
    }
    result = func_0202cbdc((void *) param0, 0, 1, param1->unk_04, param1->unk_03);
    if (result != 0) {
        return;
    }
    func_0202cbdc((void *) param0, 4, 4, param1->unk_04, param1->unk_03);
}

void func_020265c0(unsigned short *out, unsigned char *in)
{
    *out = 0xFFF1;
    if (func_0202cbdc(out, 3, 4, in[4], in[3]) != 0) {
        return;
    }
    func_0202cbdc(out, 0, 2, in[4], in[3]);
}
