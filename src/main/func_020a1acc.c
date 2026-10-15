/* func_020a1acc @ 0x020a1acc, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020a1acc {
    unsigned char pad_00[0xb4];
    int unk_B4;
} UnkStruct_020a1acc;

extern UnkStruct_020a1acc *data_021f3c3c;
extern int data_021c8188;
extern int data_020d1c20[];
extern int data_020d1bf0[];
extern int data_020d1c08[];

extern int func_02050974(void *);
extern void MI_CpuFill8(int, int, int);
extern int func_020509a8(void *, int, int, int);
extern void func_02050948(void *);
extern int func_0209f180(int);
extern int func_02050920(int, int);

int func_020a1acc(UnkStruct_020a1acc *self, int idx)
{
    int type;
    int a, b;

    type = func_02050974(&data_021c8188);
    a = data_020d1c20[idx];
    b = data_020d1bf0[idx];

    if (type == 4) {
        MI_CpuFill8(self->unk_B4, 0, b);
        func_020509a8(&data_021c8188, self->unk_B4, b, a);
        goto ret3;
    }
    if (type == 3) {
        goto case3;
    }

    func_02050948(&data_021c8188);
    if (func_0209f180(data_021f3c3c->unk_B4) == 0) {
        return 4;
    }
    if (func_02050920(self->unk_B4, data_020d1c08[idx]) != 0) {
        goto ret4b;
    }
    return 0;
ret4b:
    return 4;

case3:
    if (type == 1) {
        func_02050948(&data_021c8188);
        return 1;
    }
ret3:
    return 3;
}
