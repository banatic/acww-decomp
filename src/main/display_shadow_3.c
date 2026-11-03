/* display_shadow_3: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02001bf0 @ 0x02001bf0, 0x18 bytes, Thumb
 * func_02001bdc @ 0x02001bdc, 0x14 bytes, Thumb
 * func_02001bd0 @ 0x02001bd0, 0xc bytes, Thumb
 * func_02001bc4 @ 0x02001bc4, 0xc bytes, Thumb
 * func_02001bb4 @ 0x02001bb4, 0x10 bytes, Thumb
 * func_02001ba4 @ 0x02001ba4, 0x10 bytes, Thumb
 * func_02001b98 @ 0x02001b98, 0xc bytes, Thumb
 * func_02001b8c @ 0x02001b8c, 0xc bytes, Thumb
 */

struct UnkStruct0213fe74 {
    unsigned char bytes[0x18];
    unsigned char unk_18;
};

typedef struct {
    unsigned char pad_00[0x18];
    unsigned char byte;
} UnkStruct_02001bc4;

extern void func_02001c30(int mode);
extern void GX_SetGraphicsMode(int, int, int);
extern void func_02001c08(void *arg);
extern void GXS_SetGraphicsMode(void *arg);
extern unsigned char data_0213fe74[];

void func_02001bf0(int arg0)
{
    int r4;
    int r0;
    int r1;
    int r2;

    r4 = arg0;
    func_02001c30(arg0);
    r0 = 1;
    r1 = r4;
    r2 = r0;
    GX_SetGraphicsMode(r0, r1, r2);
}

void func_02001bdc(void *arg)
{
    func_02001c08(arg);
    GXS_SetGraphicsMode(arg);
}

unsigned char func_02001bd0(void)
{
    return (*(struct UnkStruct0213fe74 *) data_0213fe74).unk_18;
}

void func_02001bc4(unsigned char value)
{
    (*(UnkStruct_02001bc4 *) data_0213fe74).byte = value;
}

void func_02001bb4(unsigned char arg)
{
    data_0213fe74[0x18] |= arg;
}

void func_02001ba4(unsigned char mask)
{
    data_0213fe74[0x18] &= ~mask;
}

unsigned char func_02001b98(void)
{
    return data_0213fe74[0x19];
}

void func_02001b8c(unsigned char val)
{
    (*(struct _GlobalStruct { unsigned char pad_00[0x19]; unsigned char unk_19; } *) data_0213fe74).unk_19 = val;
}
