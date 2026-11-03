/* scene_command_3: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02014e2c @ 0x02014e2c, 0x18 bytes, Thumb
 * func_02014dd8 @ 0x02014dd8, 0x54 bytes, Thumb
 * func_02014d8c @ 0x02014d8c, 0x4c bytes, Thumb
 */

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x8];
    int unk_4C;
    char pad_50[0x5c];
    unsigned char unk_AC;
} UnkStruct_02014dd8;

struct UnkStruct_02014d8c {
    char pad_00[0x40];
    unsigned int unk_40;
    char pad_44[8];
    unsigned int unk_4C;
    char pad_50[92];
    char unk_AC;
};

extern int func_0201596c(int a, int b);
extern unsigned short data_020c80f8;
extern int func_02019d0c(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
extern void func_02068440(int a);
extern int func_02019e00(unsigned int a);
extern int func_02019de8(unsigned int a);
extern void func_02068434(unsigned int a);

int func_02014e2c(int arg0)
{
    int result = 0;

    if (func_0201596c(arg0, 8) != 0) {
        result = 1;
    }

    return result;
}

int func_02014dd8(UnkStruct_02014dd8 *self)
{
    if (self->unk_4C != 0 && self->unk_40 != 0) {
        if (func_02019d0c(self->unk_4C + 0x564, 0x12, 4, 0, 0, 0, 0, 0, 0, data_020c80f8, 0) != 0) {
            func_02068440(self->unk_40);
            self->unk_AC = 1;
        }
    }
    return 0;
}

int func_02014d8c(struct UnkStruct_02014d8c *param)
{
    int result = 0;
    if (param->unk_4C != 0 && param->unk_40 != 0) {
        if (func_02019e00(param->unk_4C + 0x564) == 0x12) {
            if (func_02019de8(param->unk_4C + 0x564) != 0) {
                func_02068434(param->unk_40);
                param->unk_AC = 2;
                result = 1;
            }
        }
    }
    return result;
}
