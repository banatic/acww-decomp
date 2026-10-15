/* func_0202669c @ 0x0202669c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[3];
    unsigned char unk_03;
    unsigned char unk_04;
} SrcType;

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
