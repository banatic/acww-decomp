/* scene_command_10: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020159f0 @ 0x020159f0, 0x20 bytes, Thumb
 * func_0201599c @ 0x0201599c, 0x54 bytes, Thumb
 * func_0201596c @ 0x0201596c, 0x2e bytes, Thumb
 * func_0201595c @ 0x0201595c, 0x10 bytes, Thumb
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
    char unk_68[0x44];
    char unk_AC;
    char unk_AD;
} UnkStruct_020159f0;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    short unk_14;
    unsigned short unk_16;
    int unk_18;
    char unk_1C;
    char pad_1D;
    char unk_1E;
    char unk_1F;
    char unk_20;
    char pad_21[11];
    char unk_2C;
    char pad_2D[3];
    int unk_30;
    int unk_34;
    int unk_38;
    char unk_3C;
    char unk_3D;
    char pad_3E[2];
    int unk_40;
} S0301599c;

struct UnkStruct_0201596c {
    char unk_00[0x64];
    unsigned int unk_64;
    char unk_68[0x44];
    unsigned char unk_AC;
    unsigned char unk_AD;
};

void func_0201599c(int arg0, S0301599c *ptr);
int func_0201595c(unsigned char *data);

void func_020159f0(UnkStruct_020159f0 *s)
{
    s->unk_64 = 12;
    s->unk_AC = 0;
    s->unk_AD = 0;
    func_0201599c((int) s, (S0301599c *) s->unk_68);
}

void func_0201599c(int arg0, S0301599c *ptr)
{
    ptr->unk_00 = 8;
    ptr->unk_04 = 0;
    ptr->unk_08 = 0;
    ptr->unk_0C = 0;
    ptr->unk_14 = 0;
    ptr->unk_10 = 0;
    ptr->unk_1C = 0xd;
    ptr->unk_16 = 0xfff1;
    ptr->unk_18 = 0;
    ptr->unk_1E = 0x45;
    ptr->unk_1F = 0;
    ptr->unk_20 = 2;
    ptr->unk_2C = 0xc;
    ptr->unk_30 = 2;
    ptr->unk_3C = 1;
    ptr->unk_34 = 0;
    ptr->unk_38 = 0;
    ptr->unk_3D = 0;
    ptr->unk_40 = 0;
}

int func_0201596c(struct UnkStruct_0201596c *ptr, unsigned int value)
{
    int ret = 0;
    if (ptr->unk_64 == 0xc || func_0201595c((unsigned char *) ptr) == 0) {
        ptr->unk_64 = value;
        ptr->unk_AC = 0;
        ptr->unk_AD = 1;
        ret = 1;
    }
    return ret;
}

int func_0201595c(unsigned char *data)
{
    return data[0xad] != 0;
}
