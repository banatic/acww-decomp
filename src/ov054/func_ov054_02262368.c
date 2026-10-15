/* func_ov054_02262368 @ 0x02262368, 0x60 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02262368 {
    char pad_00[0x350];
    char buf350[0x4bc];
    int unk_80C;
    unsigned short unk_810;
};

extern int func_ov054_02260474(void);
extern int func_ov054_02262494(struct UnkStruct_02262368 *self);
extern void func_ov054_02262528(struct UnkStruct_02262368 *self, int n);
extern void func_0201af1c(void *buf, int byteval);
extern int func_020e8840(void *ptr);
extern unsigned char data_ov054_0226297c[];

int func_ov054_02262368(struct UnkStruct_02262368 *self)
{
    if (func_ov054_02260474() != 0) {
        goto end;
    }
    if (func_ov054_02262494(self) != 0) {
        func_ov054_02262528(self, 3);
        func_0201af1c(&self->buf350, data_ov054_0226297c[self->unk_80C]);
    }
    if (self->unk_810 == 0xff) {
        goto end;
    }
    if (func_020e8840(&self->unk_810) != 0) {
        goto end;
    }
    func_ov054_02262528(self, 7);
end:
    return 1;
}
