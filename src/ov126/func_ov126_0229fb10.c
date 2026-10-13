/* func_ov126_0229fb10 @ 0x0229fb10, 0x48 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070c08(void *p);
extern int func_0206fc8c(void);
extern void func_02070934(void *p, const void *data, int n);
extern int func_020707e8(void *p, void *arg, unsigned char b);
extern void func_0206fc4c(int x);
extern void func_02070be8(void *p);

struct UnkStruct_0229fb10 {
    unsigned char pad_00[0xa6];
    unsigned char unk_A6;
    char pad_A7[0x4248 - 0xa7];
    char unk_4248;
};

extern unsigned char data_ov126_022a2134[];

void func_ov126_0229fb10(struct UnkStruct_0229fb10 *self)
{
    char local[0x70];
    int ret;

    func_02070c08(&local);
    ret = func_0206fc8c();
    func_02070934(&local, (void *) data_ov126_022a2134, ret);
    if (func_020707e8(&local, &self->unk_4248, self->unk_A6) == 0) {
        func_0206fc4c(0);
    }
    func_02070be8(&local);
}
