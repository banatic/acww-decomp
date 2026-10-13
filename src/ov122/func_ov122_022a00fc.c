/* func_ov122_022a00fc @ 0x022a00fc, 0x6c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

struct GlobalInfo {
    unsigned char pad_00[2];
    unsigned short flags;
};

extern struct GlobalInfo data_021fbe40;
extern int func_ov095_0229cf64(void *ptr, int val);
extern void func_ov122_022a0be4(void *ptr, int val);
extern void func_ov095_0229c8e4(void *ptr, int val);
extern void func_ov122_0229f1b4(void *ptr);
extern void func_ov002_02208098(void *ptr, int val);

int func_ov122_022a00fc(void *self)
{
    if (!(data_021fbe40.flags & 0x100)) {
        return 0;
    }
    if (func_ov095_0229cf64((char *) self + 0xc0, 12) != 0) {
        return 0;
    }
    func_ov122_022a0be4(self, 281);
    func_ov095_0229c8e4((char *) self + 0xc0, 266);
    func_ov122_0229f1b4(self);
    ((unsigned char *) self)[0xb4] = ((unsigned char *) self)[0x8d];
    func_ov002_02208098(self, 15);
    return 1;
}
