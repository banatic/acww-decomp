/* func_0206b04c @ 0x0206b04c, 0x118 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206b04c;

typedef void (UnkStruct_0206b04c::*PMF)(void);

struct UnkStruct_0206b04c {
    unsigned char pad_00[0x3c];
    int idx;
};

extern PMF data_020dee34, data_020dee4c, data_020dee64, data_020dee8c, data_020dea04, data_020de9fc, data_020de9f4,
    data_020de80c, data_020dedbc, data_020de9dc, data_020de9d4, data_020de824, data_020de9c4, data_020de9bc;

extern "C" void func_0206b04c(UnkStruct_0206b04c *obj)
{
    static PMF tbl[14] = {data_020dee34, data_020dee4c, data_020dee64, data_020dee8c, data_020dea04,
                          data_020de9fc, data_020de9f4, data_020de80c, data_020dedbc, data_020de9dc,
                          data_020de9d4, data_020de824, data_020de9c4, data_020de9bc};
    PMF f;

    f = tbl[obj->idx];
    (obj->*f)();
}
