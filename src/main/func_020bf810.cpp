/* func_020bf810 @ 0x020bf810, 0x114 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020bf810;
typedef void (UnkStruct_020bf810::*PMF)(int);
struct UnkStruct_020bf810 {
    int idx;
};

extern PMF data_020e5d88, data_020e5b58, data_020e5a50, data_020e5d70, data_020e5bf0, data_020e5a58, data_020e5c38,
    data_020e5a30, data_020e5b48, data_020e5d40, data_020e59c8, data_020e5ae8, data_020e5a78;

extern int data_021f6cd0;
extern PMF data_021f6e00[13];

extern "C" void func_020bf810(UnkStruct_020bf810 *obj, int arg)
{
    if (!(data_021f6cd0 & 1)) {
        data_021f6e00[0] = data_020e5d88;
        data_021f6e00[1] = data_020e5b58;
        data_021f6e00[2] = data_020e5a50;
        data_021f6e00[3] = data_020e5d70;
        data_021f6e00[4] = data_020e5bf0;
        data_021f6e00[5] = data_020e5a58;
        data_021f6e00[6] = data_020e5c38;
        data_021f6e00[7] = data_020e5a30;
        data_021f6e00[8] = data_020e5b48;
        data_021f6e00[9] = data_020e5d40;
        data_021f6e00[10] = data_020e59c8;
        data_021f6e00[11] = data_020e5ae8;
        data_021f6e00[12] = data_020e5a78;
        data_021f6cd0 |= 1;
    }
    PMF f;

    f = data_021f6e00[obj->idx];
    if (f) {
        (obj->*f)(arg);
    }
}
