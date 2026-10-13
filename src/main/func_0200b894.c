/* func_0200b894 @ 0x0200b894, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short unk_00;
    unsigned short pad_02;
    unsigned int unk_04;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
} UnkStruct_0200b894;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} UnkStruct_0200b894_2;

void func_0200b894(UnkStruct_0200b894 *out, UnkStruct_0200b894_2 *in, unsigned int v32, unsigned short v16, unsigned char v8)
{
    out->unk_08 = in->unk_00;
    out->unk_09 = in->unk_04;
    out->unk_04 = v32;
    out->unk_00 = v16;
    out->unk_0A = v8;
}
