/* func_ov104_0229cf14 @ 0x0229cf14, 0xd0 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

typedef struct Overlay104Data {
    unsigned char pad_00[0xb9];
    unsigned char b9;
    unsigned char pad_BA[0x22fe];
    unsigned char unk_23B8;
    unsigned char pad_23B9[0x533];
    unsigned char unk_28EC;
} Overlay104Data;

extern void func_ov104_0229c344(Overlay104Data *self, int a);
extern void func_ov002_02208d30(void *ptr, int size);
extern int func_ov104_0229d8f8(Overlay104Data *self, int param);
extern int func_0206fe54(void);
extern int func_ov002_02208d4c(void *ptr, int a, int b);
extern int func_02065ec0(int x);
extern int func_02065f18(int x);
extern void func_ov104_0229d378(Overlay104Data *self);
extern int func_ov002_02207d24(void *ptr, int v);
extern void func_ov104_0229d010(Overlay104Data *self, int param);

void func_ov104_0229cf14(Overlay104Data *self, int param1, int param2)
{
    int result;
    int v5;

    func_ov104_0229c344(self, 0x8000);
    self->b9 = param1;
    func_ov002_02208d30(&self->unk_28EC, 4);
    result = func_ov104_0229d8f8(self, param1);
    if (func_0206fe54()) {
        func_ov002_02208d4c(&self->unk_28EC, 0, 0);
    }
    v5 = func_02065ec0(result);
    if (v5 != 0) {
        if (v5 == 7) {
            func_ov002_02208d4c(&self->unk_28EC, 0x17, 1);
        } else {
            func_ov002_02208d4c(&self->unk_28EC, 0x14, 1);
        }
    }
    if (func_02065f18(result) == 0xfff1) {
        if (v5 == 3 || v5 == 6 || v5 == 1 || v5 == 4) {
            func_ov002_02208d4c(&self->unk_28EC, 0x15, 3);
        }
    }
    func_ov002_02208d4c(&self->unk_28EC, 2, 4);
    func_ov104_0229d378(self);
    if (param2 == 0) {
        func_ov002_02207d24(&self->unk_23B8, 1);
    }
    func_ov104_0229d010(self, param2);
}
