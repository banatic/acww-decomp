/* display_shadow_6: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02001d88 @ 0x02001d88, 0x18 bytes, Thumb
 * func_02001d74 @ 0x02001d74, 0x14 bytes, Thumb
 * func_02001d60 @ 0x02001d60, 0x14 bytes, Thumb
 * func_02001d44 @ 0x02001d44, 0x1c bytes, Thumb
 */

struct unk_0213fe94 {
    char pad_00[7];
    unsigned char unk_07;
};

struct unk_0213fe74 {
    char pad_00[18];
    unsigned short unk_12;
};

typedef struct {
    char pad_00[12];
    char unk_0C;
} UnkStruct_02001d74;

extern struct unk_0213fe74 data_0213fe74;
extern unsigned char data_0213fe94[0x12];
extern void func_02001d28(int param);

void func_02001d44(int cond);

void func_02001d88(unsigned char param)
{
    (*(struct unk_0213fe94 *) data_0213fe94).unk_07 = param;
    data_0213fe74.unk_12 |= 2;
}

void func_02001d74(char a, int b)
{
    (*(UnkStruct_02001d74 *) data_0213fe94).unk_0C = a;
    func_02001d44(b);
}

void func_02001d60(unsigned char param0, int param1)
{
    data_0213fe94[0x11] = param0;
    func_02001d28(param1);
}

void func_02001d44(int cond)
{
    unsigned short mask;
    unsigned short v;

    if (cond != 0) {
        mask = 4;
    } else {
        mask = 0x100;
    }

    v = (*(struct {
            char pad[0x12];
            unsigned short flags;
        } *) &data_0213fe74)
            .flags;
    v |= mask;
    (*(struct {
        char pad[0x12];
        unsigned short flags;
    } *) &data_0213fe74)
        .flags = v;
}
