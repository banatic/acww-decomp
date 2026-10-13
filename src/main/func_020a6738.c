/* func_020a6738 @ 0x020a6738, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x0c];
    unsigned char unk_0C[0x20];
    int arr[16];
} UnkStruct_020a6738;

extern int func_020a6878(UnkStruct_020a6738 *self);
extern void func_020a76d8(int *ptr, int *out);
extern void func_020a7704(unsigned char *a, unsigned char *b, unsigned char *c);
extern int func_02073dd4(int a, int b);
extern int func_020a7330(int a);
extern void func_020a7394(int a, int b, int c, int d, int e);
extern void func_020a76d0(int *ptr);
extern void func_020a682c(UnkStruct_020a6738 *self);
extern int data_020ccf94;

void func_020a6738(UnkStruct_020a6738 *self, int *out1, int *out2)
{
    int count;
    int data_val;
    int *ptr;
    unsigned char byte14;
    int local18;
    int local1c;
    int pad;
    int i;
    int flag;

    count = func_020a6878(self);
    if (count >= 4) {
        return;
    }

    ptr = &self->arr[count];
    func_020a76d8(ptr, &local18);
    if (local18 != 1) {
        return;
    }

    flag = 1;
    func_020a7704(self->unk_0C, (unsigned char *) &local1c, &byte14);

    i = 3;
    data_val = data_020ccf94;
    for (; i >= 0; i--) {
        if (count == i) {
            continue;
        }
        if (func_02073dd4(data_val, i) == 0) {
            continue;
        }
        if (func_020a7330(i) != byte14) {
            continue;
        }
        flag = 0;
        break;
    }

    func_020a7394(count, byte14, flag, 0, 7);

    func_020a76d0(ptr);
    func_020a682c(self);

    *out1 = count;
    *out2 = 7;
}
