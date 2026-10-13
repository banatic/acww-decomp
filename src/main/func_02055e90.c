/* func_02055e90 @ 0x02055e90, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055e10(void *self, void *data);
extern unsigned int FX_MulFunc(unsigned int a, unsigned int b);
extern void NNS_G3dDraw1Mat1Shp(void *a, unsigned int b, unsigned int c, unsigned int d);
extern unsigned int NNS_G3dGetSbcCmdLen(const void *p);

typedef struct Block {
    unsigned int pad_00;
    unsigned int offset;
    unsigned char pad_08[0x1c - 0x8];
    unsigned int val;
} Block;

typedef struct UnkStruct_02055e90 {
    unsigned char pad_00[0x5c];
    Block *blk;
} UnkStruct_02055e90;

void func_02055e90(UnkStruct_02055e90 *self, const unsigned int *input)
{
    Block *blk;
    unsigned char *ptr;
    unsigned int val;
    unsigned int arg;
    unsigned int arr[3];

    blk = self->blk;
    ptr = (unsigned char *) blk + blk->offset;
    val = blk->val;

    if (val == 0x1000) {
        func_02055e10(self, (void *) input);
    } else {
        if (input == 0) {
            arr[0] = arr[1] = arr[2] = val;
        } else {
            arr[0] = FX_MulFunc(input[0], val);
            arr[1] = FX_MulFunc(input[1], val);
            arr[2] = FX_MulFunc(input[2], val);
        }
        func_02055e10(self, arr);
    }

    while (1) {
        int op = *ptr & 0x1f;
        switch (op) {
            case 1:
                return;
            case 4:
                arg = ptr[1];
                break;
            case 5:
                NNS_G3dDraw1Mat1Shp(self->blk, arg, ptr[1], 1);
        }
        ptr += NNS_G3dGetSbcCmdLen(ptr);
    }
}
