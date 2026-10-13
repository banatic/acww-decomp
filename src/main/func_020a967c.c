/* func_020a967c @ 0x020a967c, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Glob1 {
    unsigned char pad1[8];
    unsigned short unk_08;
};
struct Glob2 {
    unsigned char pad2[4];
    int unk_04;
};
extern struct Glob1 data_021f4458;
extern struct Glob2 data_021f4428;
extern void func_02064658(void *a, int *b, int c, int d);
extern int func_020a9ae4(int *a);

struct UnkStruct_020a967c {
    unsigned char pad_00[0x44];
    unsigned char pad1[0x49];
    unsigned char unk_8D;
    unsigned char pad2[2];
    int unk_90;
    unsigned char pad_94[8];
    int unk_9C;
    int unk_A0;
};

int func_020a967c(struct UnkStruct_020a967c *self)
{
    int local1;
    int local2;
    int idx = self->unk_8D * 4 + 0x10;
    int flag = (data_021f4458.unk_08 - 1 == self->unk_8D) ? 1 : 0;
    int arg2;
    if (flag != 0) {
        arg2 = 4;
    } else {
        arg2 = 8;
    }
    func_02064658((char *) self + 0x44, &local1, arg2, idx + 0x20);
    self->unk_9C = func_020a9ae4(&local1);
    if (flag != 0) {
        self->unk_A0 = data_021f4428.unk_04 - (self->unk_9C + 8);
    } else {
        self->unk_A0 = func_020a9ae4(&local2) - self->unk_9C;
    }
    self->unk_90 = self->unk_9C;
    return 1;
}
