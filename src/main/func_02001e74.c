/* func_02001e74 @ 0x02001e74, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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

void func_02001e74(unsigned short a, unsigned short b)
{
    data_0213fe74.flags |= 2;
    data_0213fdf4.a = a;
    data_0213fdf4.b = b;
}
