/* func_ov003_0221f668 @ 0x0221f668, 0x74 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057a50(void *object, const char *name);
extern int data_ov003_02239a24[2];

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char *unk_5C;
} UnkStruct_0221f668;

void func_ov003_0221f668(UnkStruct_0221f668 *self, int flag)
{
    unsigned char *res = self->unk_5C;
    unsigned int i;
    unsigned char *block = res + *(int *) (res + 8);
    int zero = 0;

    for (i = 0; i < 2; i++) {
        int idx = func_02057a50((void *) (self->unk_5C), (const char *) (data_ov003_02239a24[i]));
        if (idx != ~zero) {
            unsigned char *recBase = block + 4;
            unsigned short countVal = *(unsigned short *) (block + 0xa);
            unsigned char *entries = recBase + countVal;
            unsigned short strideVal = *(unsigned short *) (recBase + countVal);
            unsigned char *entry = entries + strideVal * idx;
            int off = *(int *) (entry + 4);
            unsigned char *obj = block + off;
            if (obj != 0) {
                int v10 = *(int *) (obj + 0x10);
                v10 |= 0x800;
                *(int *) (obj + 0x10) = v10;
                if (flag) {
                    int vc = *(int *) (obj + 0xc);
                    vc |= 0x800;
                    *(int *) (obj + 0xc) = vc;
                } else {
                    int vc = *(int *) (obj + 0xc);
                    vc &= ~0x800;
                    *(int *) (obj + 0xc) = vc;
                }
            }
        }
    }
}
