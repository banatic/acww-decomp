/* func_ov098_022a2b6c @ 0x022a2b6c, 0x90 bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int header;
    int data[2];
} UnkStruct_022a2b6c;

typedef struct {
    unsigned char pad_00[0xb6];
    unsigned char byte6;
    unsigned char pad_B7[0xc4 - 0xb6 - 1];
    int unk_C4;
    unsigned char pad_C8[0x2e20 - 0xc4 - 4];
    int unk_2E20;
    int unk_2E24;
} UnkStruct_022a2b6c_2;

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} GlobalType;

extern int func_ov098_022a2bfc(void *p);
extern void func_ov096_0229fb9c(void *p);
extern void func_ov096_0229f874(void *p, int a, int b, int c);
extern int func_ov096_0229f0dc(void *p, int val);
extern int func_02043db4(int a, int *arr, int count, int flag);
extern void func_ov002_02208098(void *p, int val);
extern GlobalType *data_020ccf94;

void func_ov098_022a2b6c(UnkStruct_022a2b6c_2 *p)
{
    UnkStruct_022a2b6c local;
    int h;

    if (func_ov098_022a2bfc(p) == 0) {
        func_ov096_0229fb9c(p);
        func_ov096_0229f874(p, 13, 255, 1);
        return;
    }

    h = func_ov096_0229f0dc(p, p->byte6);
    local.data[0] = p->unk_2E20;
    local.data[1] = p->unk_2E24;
    local.header = h;
    p->unk_C4 = func_02043db4(data_020ccf94->unk_64, local.data, 2, 0);

    if (p->unk_C4 == -1) {
        func_ov096_0229fb9c(p);
        func_ov096_0229f874(p, 13, 255, 1);
    } else {
        func_ov002_02208098(p, 45);
    }
}
