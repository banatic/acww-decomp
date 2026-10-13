/* func_ov110_0229c324 @ 0x0229c324, 0x64 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c324;

extern void *data_020ccf94;
extern int func_02073d90(void *);
extern unsigned short func_02073d80(void *);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, unsigned int);
extern void func_02073770(void *, int, int);
extern void func_ov110_0229c2b8(struct UnkStruct_0229c324 *, int);
extern void MI_CpuCopy8(void *, const void *, unsigned int);

struct UnkStruct_0229c324 {
    unsigned char pad_00[0xb0];
    unsigned char arr[30];
    unsigned char pad_CE[32];
    unsigned short unk_EE;
};

void func_ov110_0229c324(struct UnkStruct_0229c324 *self, unsigned char cmd)
{
    if (func_02073d90(data_020ccf94) != 0) {
        unsigned char buf[31];
        void *p;

        func_ov110_0229c2b8(self, 8);
        buf[0] = cmd;
        MI_CpuCopy8(self->arr, buf + 1, 30);
        p = data_020ccf94;
        func_02073820(p);
        func_020737f0(p, buf, 31);
        func_02073770(p, 0x16, 4);
        self->unk_EE = func_02073d80(p);
    }
}
