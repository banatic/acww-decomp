/* func_0200acb0 @ 0x0200acb0, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} SrcType;

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
    unsigned char unk_04;
} DstType;

extern void func_020778b0(unsigned char *addr, void *arg2);

void func_0200acb0(DstType *dst, SrcType *src, void *arg2, unsigned char arg3)
{
    dst->unk_03 = (unsigned char) src->unk_00;
    dst->unk_04 = (unsigned char) src->unk_04;
    func_020778b0(&dst->unk_01, arg2);
    dst->unk_00 = arg3;
}
