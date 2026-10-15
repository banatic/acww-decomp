/* func_ov050_02262f48 @ 0x02262f48, 0xe0 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02262f48_3 {
    unsigned char pad_00[0x73e];
    unsigned char unk_73E;
};

struct UnkStruct_02262f48 {
    unsigned char pad_00[0x40];
    void *unk_40;
    unsigned char pad_44[0x70];
    struct UnkStruct_02262f48_3 *unk_B4;
};

struct UnkStruct_02262f48_2 {
    unsigned char pad_00[4];
    unsigned char unk_04;
};

extern int func_ov050_02263394(struct UnkStruct_02262f48 *a, struct UnkStruct_02262f48_2 *b);
extern int func_020984e8(void);
extern void *func_02099640(int argument0);
extern void *func_0209ad9c(void *a, int b);
extern void *func_0209b4d4(void *object);
extern void *func_0209b4cc(void *a, int b);
extern void *func_02094fd4(void *local);
extern int func_0209bba0(void *handle);
extern int func_02003618(void *h, void *local);
extern void func_02068404(void *a, int b, void *local);
extern void *func_02094fbc(void *local);

void func_ov050_02262f48(struct UnkStruct_02262f48 *self, struct UnkStruct_02262f48_2 *status)
{
    char local[0x24];
    void *handle;
    void *handle2;

    if (func_ov050_02263394(self, status) != 0) {
        return;
    }

    handle = func_0209ad9c(func_02099640((int) func_020984e8()), 0);
    handle2 = func_0209b4d4((void *) handle);
    handle = func_0209b4cc(handle, 1);
    func_02094fd4(local);

    if (func_0209bba0(handle2) == 2) {
        status->unk_04 = 0x28;
        func_02094fbc(local);
        return;
    }
    if (func_0209bba0(handle2) == 0) {
        if (self->unk_B4->unk_73E == 0 || self->unk_B4->unk_73E == 2) {
            if (handle != 0) {
                func_02003618(handle, local);
                func_02068404(self->unk_40, 0, local);
            }
            status->unk_04 = 0x21;
            if (self->unk_B4->unk_73E == 2) {
                self->unk_B4->unk_73E = 1;
            }
        } else {
            status->unk_04 = 0x10;
        }
        func_02094fbc(local);
        return;
    }
    if (func_0209bba0(handle2) == 1) {
        if (handle != 0) {
            func_02003618(handle, local);
            func_02068404(self->unk_40, 0, local);
        }
        status->unk_04 = 0x27;
        func_02094fbc(local);
        return;
    }
    func_02094fbc(local);
}
