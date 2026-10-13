/* func_02084dc8 @ 0x02084dc8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern const unsigned int data_021fbee8[3];

typedef struct {
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned short d;
    unsigned char e;
    unsigned char unk_0F;
} UnkStruct_02084dc8;

void func_02084dc8(UnkStruct_02084dc8 *out, const unsigned short *p_u16, unsigned char b1, unsigned char b2,
                   const UnkStruct_02084dc8 *src)
{
    out->d = *p_u16;
    out->e = b1;
    out->unk_0F = b2;
    if (src) {
        out->a = src->a;
        out->b = src->b;
        out->c = src->c;
    } else {
        out->a = data_021fbee8[0];
        out->b = data_021fbee8[1];
        out->c = data_021fbee8[2];
    }
}
