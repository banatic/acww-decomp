/* func_ov097_022a27fc @ 0x022a27fc, 0xe8 bytes, Thumb, module ov097
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022a27fc UnkStruct_022a27fc;
struct UnkStruct_022a27fc {
    unsigned char pad_00[0xc4];
    int unk_C4;
};

typedef struct UnkStruct_022a27fc_2 UnkStruct_022a27fc_2;
struct UnkStruct_022a27fc_2 {
    unsigned char pad_00[0x64];
    int unk_64;
};

extern UnkStruct_022a27fc_2 *data_020ccf94;

extern void func_02061b1c(unsigned short *out, unsigned short *in, int flag);
extern int func_0204bcdc(unsigned short *ptr);
extern int func_ov004_0223b540(int *out, unsigned short *in, int flag);
extern void func_ov096_0229fb9c(UnkStruct_022a27fc *self);
extern void func_ov096_0229f874(UnkStruct_022a27fc *self, int a, int b, int c);
extern void func_0200467c(int cmd);
extern int func_020435fc(int value, unsigned short param);
extern int func_ov004_0223c660(int value);

int func_ov097_022a27fc(UnkStruct_022a27fc *self, unsigned short param2)
{
    unsigned short a = param2;
    unsigned short b;
    int c;

    func_02061b1c(&b, &a, 0);
    if (func_0204bcdc(&b) != 0) {
        int code = func_ov004_0223b540(&c, &b, 1);
        switch (code) {
            case 0:
                func_ov096_0229fb9c(self);
                func_ov096_0229f874(self, 3, 0xff, 0);
                func_0200467c(0x73);
                return 0;
            case 1:
                func_ov096_0229fb9c(self);
                func_ov096_0229f874(self, 5, 0xff, 1);
                func_0200467c(0x73);
                return 0;
            case 2:
                func_ov096_0229fb9c(self);
                func_ov096_0229f874(self, 3, 0xff, 0);
                func_0200467c(0x73);
                return 0;
            default:
                func_ov004_0223c660(c);
                goto ret_1;
        }
    } else {
        int ret = func_020435fc(data_020ccf94->unk_64, param2);
        self->unk_C4 = ret;
        if (self->unk_C4 == -1) {
            func_ov096_0229fb9c(self);
            func_ov096_0229f874(self, 3, 0xff, 0);
            func_0200467c(0x73);
            return 0;
        } else {
            return 2;
        }
    }
ret_1:
    return 1;
}
