/* func_020ace24 @ 0x020ace24, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e40e0;
extern int func_02065604(int *ptr, int val);
extern __arm void NNS_G3dMdlSetMdlDiff(unsigned int arg0, int arg1, unsigned short arg2);

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned int unk_5C;
} UnkStruct_020ace24;

extern UnkStruct_020ace24 data_021f472c;

void func_020ace24(void)
{
    volatile unsigned short a, b;

    data_020e40e0 = 1;
    a = (unsigned short) func_02065604(&data_020e40e0, 1);
    b = a;
    NNS_G3dMdlSetMdlDiff(data_021f472c.unk_5C, 0, b);
}
