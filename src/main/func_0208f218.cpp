/* func_0208f218 @ 0x0208f218, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a8bb8(void *);
extern "C" void func_02051648(void *);
extern "C" void func_02051694(void *);

struct UnkStruct_0208f218 {
    virtual int f0();
    virtual int f1();
    virtual int f2();
    virtual int f3();
    char pad[0x25];
    char flag;
};

struct Field48 {
    char pad[0x10];
    int unk_10;
};

struct UnkStruct_0208f218_2 {
    char pad_00[0x48];
    Field48 *unk_48;
    UnkStruct_0208f218 sub;
};

extern "C" void func_0208f218(UnkStruct_0208f218_2 *self)
{
    func_020a8bb8(&self->sub);
    Field48 *p = self->unk_48;
    if (p) {
        p->unk_10 = self->sub.f3();
        func_02051648(self->unk_48);
        func_02051694(self->unk_48);
        self->sub.flag = 1;
    }
}
