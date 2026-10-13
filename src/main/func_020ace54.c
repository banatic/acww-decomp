/* func_020ace54 @ 0x020ace54, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020ace54 {
    char pad_00[0x5c];
    unsigned char *unk_5C;
};

extern struct UnkStruct_020ace54 data_021f472c;
extern int data_020e40e4;
extern unsigned char *data_021f471c;
extern int data_020e40e0;

int func_020555c8(struct UnkStruct_020ace54 *a, int *b, int c);
void NNSi_G3dModifyMatFlag(unsigned char *a, int b, int c);

int func_020ace54(void)
{
    int r4;
    unsigned char *a;
    unsigned char *p;
    unsigned short off;
    unsigned int delta;
    unsigned char *result;

    if (func_020555c8(&data_021f472c, &data_020e40e4, 0) != 0) {
        r4 = 1;
    } else {
        r4 = 0;
    }

    a = data_021f472c.unk_5C;
    p = a + *(unsigned int *) (a + 8);
    off = *(unsigned short *) (p + 0xa);
    delta = *(unsigned int *) (p + off + 8);
    result = p + delta;
    data_021f471c = result;
    data_020e40e0 = 1;
    NNSi_G3dModifyMatFlag(a, 1, 0x40);

    return r4;
}
