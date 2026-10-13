/* func_ov137_0229cdf4 @ 0x0229cdf4, 0x7c bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

typedef struct UnkStruct_0229cdf4 UnkStruct_0229cdf4;
struct UnkStruct_0229cdf4 {
    unsigned char pad_00[0xf8];
    unsigned char unk_F8;
    unsigned char pad_F9[0x2c4 - 0xf8 - 1];
    unsigned char unk_2C4;
};

extern int func_ov002_02208054(UnkStruct_0229cdf4 *p, int a);
extern int func_ov002_0220a784(void *p, int a);
extern int func_ov134_0229ab2c(void *p, unsigned char a, unsigned char b);
extern void func_ov137_0229c998(UnkStruct_0229cdf4 *p);
extern void func_ov137_0229c92c(UnkStruct_0229cdf4 *p);
extern void func_ov137_0229c900(UnkStruct_0229cdf4 *p, int a);

void func_ov137_0229cdf4(UnkStruct_0229cdf4 *self)
{
    if (func_ov002_02208054(self, 1)) {
        func_ov137_0229c998(self);
        return;
    }
    {
        unsigned int flag = (data_021fbdd8 != 0 && data_021fbddc != 0);
        if (flag > 0) {
            if (func_ov002_0220a784(&self->unk_F8, 6)) {
                func_ov137_0229c92c(self);
                return;
            }
            {
                int ret = func_ov134_0229ab2c(&self->unk_2C4, data_021f6c58, data_021f6c54);
                if (ret == 6) {
                    return;
                }
                func_ov137_0229c900(self, ret);
            }
        }
    }
}
