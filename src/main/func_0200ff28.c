/* func_0200ff28 @ 0x0200ff28, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x800];
    int unk_800;
    unsigned char pad_804[0x80c - 0x804];
    int unk_80C;
} UnkStruct_0200ff28;

extern int data_021c80bc;
extern void func_0204f818(int *out1, int *out2, void *arg1);
extern int func_02043a4c(int a, void *buf, int val);
extern int func_02043d84(int a, void *buf, int val, int flag, int extra);
extern int func_02043990(int a, void *buf, int val);
extern int data_020c7640[];

int func_0200ff28(UnkStruct_0200ff28 *self, void *arg1, int mode, int idx)
{
    if (self->unk_80C == -1 && data_021c80bc != 0) {
        int v1, v2;

        v1 = 0;
        v2 = 0;
        func_0204f818(&v1, &v2, arg1);

        switch (mode) {
            case 0: {
                struct {
                    int a, b;
                } buf;
                buf.a = v1;
                buf.b = v2;
                self->unk_80C = func_02043a4c(self->unk_800, &buf, data_020c7640[idx]);
                break;
            }
            case 1: {
                struct {
                    int a, b;
                } buf;
                buf.a = v1;
                buf.b = v2;
                self->unk_80C = func_02043d84(self->unk_800, &buf, data_020c7640[idx], 0, 0xfff1);
                break;
            }
            case 2: {
                struct {
                    int a, b;
                } buf;
                buf.a = v1;
                buf.b = v2;
                self->unk_80C = func_02043990(self->unk_800, &buf, data_020c7640[idx]);
                break;
            }
        }
    }

    return self->unk_80C != -1;
}
