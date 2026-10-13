/* func_0200b7c0 @ 0x0200b7c0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020778b0(unsigned char *dst, int param);

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
} UnkStruct_0200b7c0;

void func_0200b7c0(UnkStruct_0200b7c0 *dst, const unsigned int *src, unsigned char byte1, int param4, unsigned char byte2)
{
    dst->unk_04 = (unsigned char) src[0];
    dst->unk_05 = (unsigned char) src[1];
    dst->unk_03 = byte1;
    func_020778b0(&dst->unk_01, param4);
    dst->unk_00 = byte2;
}
