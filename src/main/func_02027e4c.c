/* func_02027e4c @ 0x02027e4c, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Pair {
    int a;
    int b;
};
struct UnkStruct_02027e4c {
    char pad_00[0x830];
    int value;
};
struct UnkStruct_02027e4c_2 {
    char pad_00[0xc8];
    struct Pair unk_C8;
    char pad_D0[0x100 - 0xd0];
    struct UnkStruct_02027e4c *sub;
    char buf[0x1e];
    unsigned char byte;
    char pad_123[0x160 - 0x123];
    void *ptr;
};
struct UnkStruct_02027e4c_3 {
    int unk_00;
    unsigned char unk_04;
};
struct UnkStruct_02027e4c_4 {
    void *ptr;
    unsigned char byte;
};
extern struct UnkStruct_02027e4c_3 data_020c8998;
extern struct UnkStruct_02027e4c_3 data_020c8a40;
extern struct Pair data_020d8df0;
extern void func_0202d9c4(void *self);
extern int func_0209bc40(void);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202da38(void *self, char *buf, unsigned char *byte, int count, int v1, int v2, int v3, int zero1, int zero2);
extern int func_0209b4cc(void *ptr, int idx);
extern void func_02015e10(void *self, int value, int idx);
extern int func_0209bb70(void);
extern void func_02015de4(void *self, int value, int a, int b);
void func_02027e4c(struct UnkStruct_02027e4c_2 *self, struct UnkStruct_02027e4c_4 *out)
{
    struct UnkStruct_02027e4c_3 *dp = 0;
    int v;
    int res;
    int tmp;
    func_0202d9c4(self);
    v = func_0209bc40();
    switch (v) {
        case 10:
            dp = &data_020c8998;
            break;

        case 19:
            dp = &data_020c8a40;
            break;
    }

    if (dp != 0) {
        res = func_0208150c(self->sub->value);
        res = func_020036e8(res);
        func_0202da38(self, self->buf, &self->byte, 30, res, dp->unk_00, dp->unk_04, 0, 0);
        if (self->ptr != 0) {
            tmp = func_0209b4cc(self->ptr, 0);
            func_02015e10(self, tmp, 0);
            tmp = func_0209b4cc(self->ptr, 1);
            func_02015e10(self, tmp, 1);
            func_0202d9c4(self);
            tmp = func_0209bb70();
            func_02015de4(self, tmp, 0, 7);
        }
    }
    out->ptr = &self->buf;
    out->byte = self->byte;
    self->unk_C8 = data_020d8df0;
}
