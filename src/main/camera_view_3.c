/* camera_view_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203c99c @ 0x0203c99c, 0x14 bytes, Thumb
 * func_0203c97c @ 0x0203c97c, 0x20 bytes, Thumb
 */

struct Src {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
};

struct Dst {
    char pad_00[0xb8];
    unsigned int unk_B8;
    unsigned int unk_BC;
    unsigned int unk_C0;
    unsigned int unk_C4;
};

extern char data_020ca1ac[];

void func_0203c97c(struct Dst *dst, struct Src *src);

void func_0203c99c(int a, int b)
{
    func_0203c97c((struct Dst *) a, (struct Src *) (data_020ca1ac + (b << 4)));
}

void func_0203c97c(struct Dst *dst, struct Src *src)
{
    dst->unk_B8 = src->unk_00;
    dst->unk_BC = src->unk_04;
    dst->unk_C0 = src->unk_08;
    dst->unk_C4 = src->unk_0C;
}
