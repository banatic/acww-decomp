/* func_02020168 @ 0x02020168, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_02020a5c(void *self, int arg);
extern "C" int func_020819bc(int value);
extern "C" int func_020644cc(int value);
extern "C" void func_0202da88(void *self, const char *str);
extern "C" void func_0202d8f8(void *self, int *a, int *b, int val, int flag);

extern const char data_021c22d4[];
extern const char data_021c2304[];
extern const char data_021c2364[];

class UnkStruct_02020168 {
  public:
    unsigned char pad_00[0xB0];
    void (UnkStruct_02020168::*pmf)(int);
    unsigned char pad_B8[0x100 - 0xB8];
    void *unk_100;
    unsigned char pad_104[0x128 - 0x104];
    int unk_128;
    int unk_12C;
};

extern "C" void func_02020168(UnkStruct_02020168 *self, int arg1)
{
    if (func_02020a5c(self, arg1) != 0) {
        func_0202d8f8(self, &self->unk_12C, &self->unk_128, *(int *) ((char *) self->unk_100 + 0x830), 0);
        return;
    } else {
        if (self->unk_12C == 0 || func_020819bc(self->unk_12C) == 0) {
            func_0202da88(self, data_021c22d4);
        } else {
            if (func_020644cc(100) < 30) {
                func_0202da88(self, data_021c2304);
            } else {
                func_0202da88(self, data_021c2364);
            }
        }
        func_0202d8f8(self, &self->unk_12C, &self->unk_128, *(int *) ((char *) self->unk_100 + 0x830), 0);
        if (self->pmf) {
            (self->*self->pmf)(arg1);
        }
    }
}
