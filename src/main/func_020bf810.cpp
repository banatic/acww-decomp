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

extern "C" void func_020bf810(UnkStruct_020bf810 *obj, int arg)
{
    static PMF tbl[13] = {data_020e5d88, data_020e5b58, data_020e5a50, data_020e5d70, data_020e5bf0,
                          data_020e5a58, data_020e5c38, data_020e5a30, data_020e5b48, data_020e5d40,
                          data_020e59c8, data_020e5ae8, data_020e5a78};
    PMF f;

    f = tbl[obj->idx];
    if (f) {
        (obj->*f)(arg);
    }
}
