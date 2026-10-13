/* func_ov098_022a2ec0 @ 0x022a2ec0, 0x6c bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073d90(void *ptr);
extern void func_020779b8(char *dst, int a, int b);
extern void MI_CpuCopy8(char *dst, char *src, int len);
extern void func_02073820(void *ptr);
extern void func_020737f0(void *ptr, char *buf, int len);
extern void func_02073770(void *ptr, int a, int b);

struct BigStruct {
    unsigned char pad_00[0x2e14];
    int unk_2E14;
    unsigned char pad_2E18[4];
    int unk_2E1C;
};

void func_ov098_022a2ec0(struct BigStruct *obj, char a, char b)
{
    if (func_02073d90(data_020ccf94)) {
        char buffer[16];
        void *ptr;
        buffer[0] = b;
        buffer[1] = a;
        func_020779b8(buffer + 7, obj->unk_2E14, obj->unk_2E1C);
        MI_CpuCopy8(buffer + 7, buffer + 2, 5);
        ptr = data_020ccf94;
        func_02073820(ptr);
        func_020737f0(ptr, buffer, 7);
        func_02073770(ptr, 22, 4);
    }
}
