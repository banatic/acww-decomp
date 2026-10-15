/* func_020c3838 @ 0x020c3838, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020c3838 {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[4];
    int unk_64;
    char pad_68[0x348];
    char unk_3B0;
    char pad_3B1[0x15f];
    char unk_510;
};

extern int func_0202ec58(struct UnkStruct_020c3838 *self);
extern int func_020984e8(void);
extern void func_020c3690(struct UnkStruct_020c3838 *self, int b);
extern int func_020b65c4(void);
extern void func_0201ad18(void *p, int a, int b, int c, int d, int e, int f, int g);
extern int data_020c814c;

extern unsigned char data_021fbee8[];

int func_020c3838(struct UnkStruct_020c3838 *self)
{
    int a;
    a = func_0202ec58(self);
    if (a == 0) {
        return 0;
    }
    func_020984e8();
    if ((((int) (func_020c3690(self, 0), self)), func_020b65c4()) == 0x2f) {
        self->unk_510 = 0;
        func_0201ad18(&self->unk_3B0, 0, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
        self->unk_5C = 0x10000;
        self->unk_64 = 0x16800;
    }
    return 1;
}
