/* func_0203bb8c @ 0x0203bb8c, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[4];
    unsigned char unk_04;
} G1T;
typedef struct {
    int v[3];
} Row;

typedef struct {
    unsigned char pad_00[0x1e4];
    int unk_1E4;
    int unk_1E8;
    int unk_1EC;
    int unk_1F0;
    unsigned char pad_1F4[0x1f5 - 0x1f4];
    unsigned char unk_1F5;
    unsigned char pad_1F6[0x1fc - 0x1f6];
    int unk_1FC;
} SelfT;

extern G1T *data_021f6948;
extern Row data_020ca158[];
extern void func_0203caa4(SelfT *self, int a, int b);
extern void func_0203c99c(SelfT *self, int a);
extern void func_0203ad58(void);
extern void func_0203ad68(void);
extern void func_0203ab34(SelfT *self, int a);

int func_0203bb8c(SelfT *self)
{
    if (data_021f6948->unk_04 == 0) {
        int value;

        if (self->unk_1FC == 2) {
            self->unk_1F5 = 0;
        }

        value = data_020ca158[self->unk_1F0].v[self->unk_1EC];
        func_0203caa4(self, value, 0);
    } else {
        func_0203caa4(self, 0, 0);
    }

    func_0203c99c(self, 0);

    {
        int st = self->unk_1FC;
        if (st == 2 || st == 4 || st == 0x10 || st == 5 || st == 6 || st == 0x12 || (unsigned int) (st - 0xb) <= 1) {
            func_0203ad58();
            self->unk_1E4 = 0;
        } else {
            self->unk_1E4 = 0;
            self->unk_1E8 = 0;
            func_0203ad68();
        }
    }

    if (self->unk_1FC == 2 || self->unk_1FC == 0x10) {
        func_0203ab34(self, 0x30);
    }

    return 1;
}
