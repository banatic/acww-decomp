/* func_0203b618 @ 0x0203b618, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov004_02247438(void *, int);
extern "C" void func_ov003_02236564(void *);
extern "C" void func_0203c99c(void *, int);
extern "C" void func_0203ad68(void);
extern "C" void func_0203ad58(void);
extern "C" void func_0203ab34(void *, int);
extern "C" void func_0203caa4(void *, int, void *);

struct GlobalPtr {
    char pad_00[4];
    unsigned char cond;
};
extern GlobalPtr *data_021f6948;

struct MainObj {
    char pad_00[0x1f6];
    char unk_1F6;
    char pad_1F7[5];
    int unk_1FC;
};

extern "C" int func_0203b618(MainObj *self)
{
    if (data_021f6948->cond == 0) {
        func_0203caa4(self, 0xb, 0);
        self->unk_1F6 = 3;
        func_ov004_02247438(self, 0);
    } else {
        func_0203caa4(self, 0xa, 0);
        func_ov003_02236564(self);
    }
    func_0203c99c(self, 0);
    if (self->unk_1FC == 1) {
        func_0203ad68();
    } else {
        func_0203ad58();
    }
    func_0203ab34(self, 0x2f);
    return 1;
}
