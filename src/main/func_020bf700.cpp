/* func_020bf700 @ 0x020bf700, 0x110 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020bf700;
typedef void (UnkStruct_020bf700::*PMF)(void);
struct UnkStruct_020bf700 {
    int idx;
};

extern PMF data_020e5c90, data_020e5a80, data_020e5be8, data_020e5ca8, data_020e5cf8, data_020e5d00, data_020e5cb0;
extern PMF data_020e5b70, data_020e59f8, data_020e5d68, data_020e5ad8, data_020e5ae0, data_020e5d18;

extern "C" void func_020bf700(UnkStruct_020bf700 *p)
{
    static PMF tbl[13] = {data_020e5c90, data_020e5a80, data_020e5be8, data_020e5ca8, data_020e5cf8,
                          data_020e5d00, data_020e5cb0, data_020e5b70, data_020e59f8, data_020e5d68,
                          data_020e5ad8, data_020e5ae0, data_020e5d18};
    PMF f;

    f = tbl[p->idx];
    if (f) {
        (p->*f)();
    }
}
