/* __sinit_020c73d4 @ 0x020c73d4, 0xdc bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    long a, b;
} UnkStruct_020c73d4;
extern struct {
    long f0;
    UnkStruct_020c73d4 f4;
} data_021fcff8;
extern struct {
    UnkStruct_020c73d4 f0;
} data_0213e838;
extern struct {
    long f0;
    long f4;
    UnkStruct_020c73d4 f8;
} data_021fd014;
extern struct {
    UnkStruct_020c73d4 f0;
} data_0213e848;
extern struct {
    long f0;
    long f4;
    UnkStruct_020c73d4 f8;
} data_021fd004;
extern struct {
    UnkStruct_020c73d4 f0;
} data_0213e820;
extern struct {
    long f0;
    long f4;
    UnkStruct_020c73d4 f8;
} data_021fd024;
extern struct {
    UnkStruct_020c73d4 f0;
} data_0213e840;
extern struct {
    long f0;
    long f4;
    UnkStruct_020c73d4 f8;
} data_021fd034;
extern struct {
    UnkStruct_020c73d4 f0;
} data_0213e828;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c73d4(void)
{
    data_021fcff8.f4 = data_0213e838.f0;
    data_021fcff8.f0 = 0;
    data_021fd014.f0 = 0;
    data_021fd014.f4 = 0;
    data_021fd014.f8 = data_0213e848.f0;
    data_021fd004.f0 = 0;
    data_021fd004.f4 = 0;
    data_021fd004.f8 = data_0213e820.f0;
    data_021fd024.f0 = 0;
    data_021fd024.f4 = 0;
    data_021fd024.f8 = data_0213e840.f0;
    data_021fd034.f0 = 0;
    data_021fd034.f4 = 0;
    data_021fd034.f8 = data_0213e828.f0;
}

#pragma section INIT end
