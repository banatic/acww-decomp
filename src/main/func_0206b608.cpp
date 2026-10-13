/* func_0206b608 @ 0x0206b608, 0x148 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206b608;
typedef void (UnkStruct_0206b608::*PMF)(void);

struct UnkStruct_0206b608 {
    unsigned char pad_00[0x3c];
    int unk_3C;
};

extern PMF data_020decb4, data_020decac, data_020de95c, data_020dec9c, data_020dec94, data_020de89c, data_020de8a4,
    data_020dec7c, data_020dec74, data_020dec6c, data_020de93c, data_020dec5c, data_020dec54, data_020de92c, data_020de8bc,
    data_020dec3c, data_020de924;

extern "C" void func_0206b608(UnkStruct_0206b608 *obj)
{
    static PMF tbl[17] = {data_020decb4, data_020decac, data_020de95c, data_020dec9c, data_020dec94, data_020de89c,
                          data_020de8a4, data_020dec7c, data_020dec74, data_020dec6c, data_020de93c, data_020dec5c,
                          data_020dec54, data_020de92c, data_020de8bc, data_020dec3c, data_020de924};
    PMF f;

    f = tbl[obj->unk_3C];
    (obj->*f)();
}
