/* func_ov003_0221b294 @ 0x0221b294, 0x8c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c67a4;
extern int data_020ca0ec;
extern int func_020ea990(int, void *);
extern int FX_Div(int, int);
extern void func_02055e7c(void *, void *);
extern void func_020acc0c(void *, int, int, int);

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[0x134 - 0x60];
    int unk_134;
    char pad_138[0x1d0 - 0x138];
    int unk_1D0;
    char pad_1D4[0x26c - 0x1d4];
    int unk_26C;
    char pad_270[0x39c - 0x270];
    int unk_39C;
} UnkStruct_0221b294;

extern unsigned char data_021c67d0[];

int func_ov003_0221b294(UnkStruct_0221b294 *self)
{
    int result;
    int arr[3];

    if (data_021c67a4 != 0 && func_020ea990((unsigned int) data_021c67d0, &self->unk_5C) <= data_020ca0ec) {
        result = FX_Div(self->unk_26C, 0x1000);
        arr[0] = result;
        arr[1] = result;
        arr[2] = result;

        if (self->unk_39C == 0xb) {
            func_02055e7c(&self->unk_1D0, arr);
        } else {
            func_02055e7c(&self->unk_134, arr);
        }

        func_020acc0c(&self->unk_5C, self->unk_26C, 0x4000, 0x1000);
    }

    return 1;
}
