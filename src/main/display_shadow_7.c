/* display_shadow_7: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02001ec4 @ 0x02001ec4, 0x8 bytes, Thumb
 * func_02001ea8 @ 0x02001ea8, 0x1c bytes, Thumb
 * func_02001e94 @ 0x02001e94, 0x12 bytes, Thumb
 * func_02001e74 @ 0x02001e74, 0x20 bytes, Thumb
 */

struct FlagsStruct {
    char pad_00[0x11];
    unsigned char flags;
};

struct StoreStruct {
    char pad_00[4];
    unsigned short a;
    unsigned short b;
};

extern struct FlagsStruct data_0213fe74;
extern struct StoreStruct data_0213fdf4;

void func_02001ec4(unsigned short *p0)
{
    p0[0] = 0;
    p0[1] = 0;
}

void func_02001ea8(unsigned int *arg0)
{
    arg0[0] = 0x1000;
    arg0[1] = 0;
    arg0[2] = 0;
    arg0[3] = 0x1000;
    arg0[4] = 0;
    arg0[5] = 0;
    arg0[6] = 0;
    arg0[7] = 0;
}

void func_02001e94(unsigned char *r0)
{
    r0[0] = 0;
    r0[1] = 0;
    r0[2] = 0xff;
    r0[3] = 0xc0;
    r0[4] = 0;
}

void func_02001e74(unsigned short a, unsigned short b)
{
    data_0213fe74.flags |= 2;
    data_0213fdf4.a = a;
    data_0213fdf4.b = b;
}
