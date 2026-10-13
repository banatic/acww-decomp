/* func_ov068_02270df8 @ 0x02270df8, 0x88 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern char *func_020961a8(int);
extern int func_0200322c(void *, void *);
extern void *func_0209d088(void *);
extern void NNS_G3dMdlSetMdlAlpha(void *, int, int);
extern void func_02035684(int, int, int);

typedef struct {
    unsigned char pad_00[0xf4];
    unsigned int unk_F4;
    unsigned char pad_F8[0x130 - 0xf8];
    unsigned char unk_130[0x204 - 0x130];
    unsigned char unk_204[0x210 - 0x204];
    unsigned int unk_210[3];
    unsigned int unk_21C;
    unsigned char pad_220[0x232 - 0x220];
    unsigned short unk_232;
    unsigned char pad_234[0x23a - 0x234];
    unsigned short unk_23A;
    unsigned char pad_23C[0x251 - 0x23c];
    unsigned char unk_251;
} UnkStruct_02270df8;

void func_ov068_02270df8(UnkStruct_02270df8 *obj)
{
    char *ret;
    unsigned int *arr;
    void *p;
    int val;

    ret = func_020961a8(4);
    arr = obj->unk_210;

    if (ret != 0) {
        val = func_0200322c(&obj->unk_204, ret + 0x5c);
        obj->unk_23A = (unsigned short) val;
    }

    p = func_0209d088(obj->unk_130);
    NNS_G3dMdlSetMdlAlpha(p, 0, 0x1f);

    obj->unk_251 = 2;
    arr[0] = 1;
    arr[1] = 1;
    arr[2] = 1;
    obj->unk_232 = 0x28;
    obj->unk_F4 = 0x2d000;
    obj->unk_21C = 0xf0;

    func_02035684(25, 0, 0);
}
