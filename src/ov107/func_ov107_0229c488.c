/* func_ov107_0229c488 @ 0x0229c488, 0x68 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073d90(int);
extern void func_020779b8(char *dst, int a, int b);
extern void MI_CpuCopy8(char *dst, char *src, int count);
extern void func_02073820(int val);
extern void func_020737f0(int val, char *ptr, int count);
extern void func_02073770(int val, int a, int b);

struct UnkStruct_0229c488 {
    char pad_00[0xc0];
    unsigned int unk_C0;
    char pad_C4[4];
    unsigned int unk_C8;
};

void func_ov107_0229c488(struct UnkStruct_0229c488 *param0, int param1)
{
    char a[4];
    char b[5];

    if (func_02073d90(data_020ccf94) != 0) {
        int v;

        a[0] = 2;
        a[1] = param1;
        func_020779b8(&b[3], param0->unk_C0, param0->unk_C8);
        MI_CpuCopy8(&b[3], &a[2], 5);
        v = data_020ccf94;
        func_02073820(v);
        func_020737f0(v, a, 7);
        func_02073770(v, 0x16, 4);
    }
}
