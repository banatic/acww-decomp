/* func_02060214 @ 0x02060214, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02060214;
typedef void (UnkStruct_02060214::*Pmf)();
struct Entry {
    Pmf pmf;
};
extern Entry data_021cad30[];
extern int data_021cad80;
class UnkStruct_02060214 {
  public:
    unsigned char unk_00;
    char pad_01[3];
    int unk_04;
    char pad_08[0x30 - 8];
    int unk_30;
    char pad_34[4];
    unsigned char unk_38;
};
extern "C" int func_0206053c(void *, unsigned char);
extern "C" void func_0206026c(void *, int);
extern "C" void func_02060214(UnkStruct_02060214 *self)
{
    func_0206053c(&data_021cad80, self->unk_00);
    self->unk_30++;
    self->unk_38 = 0;
    if (self->unk_04 >= 10) {
        func_0206026c(self, 0);
    }
    (self->*(data_021cad30[self->unk_04].pmf))();
}
