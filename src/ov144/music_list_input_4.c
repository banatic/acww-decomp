/* music_list_input_4: 3 functions, module ov144
 * mwccarm 1.2/base -O4,s
 * func_ov144_0229a264 @ 0x0229a264, 0x36 bytes, Thumb
 * func_ov144_0229a208 @ 0x0229a208, 0x5c bytes, Thumb
 * func_ov144_0229a198 @ 0x0229a198, 0x70 bytes, Thumb
 */

typedef struct UnkStruct_0229a264 UnkStruct_0229a264;

struct UnkStruct_0229a264 {
    unsigned char pad_00[0xc4];
    int unk_C4;
};

extern void func_ov144_0229a0e0(UnkStruct_0229a264 *self);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_ov002_0220a374(void *ptr, int a);
extern int func_ov002_0220a768(unsigned char *, int);
extern int func_ov002_0220a4f8(unsigned char *);
extern int func_ov002_0220a72c(char *ptr, int arg);
extern int func_ov002_0220a4d4(char *ptr);

int func_ov144_0229a208(unsigned char *p);
int func_ov144_0229a198(char *p);

void func_ov144_0229a264(UnkStruct_0229a264 *self)
{
    int a;
    int b;

    a = func_ov144_0229a208((unsigned char *) self);
    b = func_ov144_0229a198((char *) self);
    func_ov002_0220a0b4(&self->unk_C4, a, b);
    func_ov002_0220a374(&self->unk_C4, 1);
    func_ov144_0229a0e0(self);
}

int func_ov144_0229a208(unsigned char *p)
{
    unsigned char b = p[0xc1];

    if (b <= 8) {
        return 0x48;
    }

    switch (b) {
        case 9:
            return func_ov002_0220a768(p + 0x170, 6);
        case 11:
        case 12:
        case 13:
            return 0x26;
        case 10:
            return func_ov002_0220a4f8(p + 0x128);
        default:
            return 0x80;
    }
}

int func_ov144_0229a198(char *p)
{
    unsigned char b = (unsigned char) p[0xC1];
    if (b <= 8) {
        unsigned int word = *(unsigned int *) (p + 0xA0);
        return ((b << 4) + 0x20) - (word & 0xF);
    } else {
        switch (b) {
            case 9:
                return func_ov002_0220a72c(p + 0x170, 6);
            case 11:
                return 0x2A;
            case 12:
                return 0x7D;
            case 13:
                return 0x65;
            case 10:
                return func_ov002_0220a4d4(p + 0x128);
            default:
                return 0x60;
        }
    }
}
