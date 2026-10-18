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

extern int data_021cda64;
extern PMF data_021cde64[17];

extern "C" void func_0206b608(UnkStruct_0206b608 *obj)
{
    if (!(data_021cda64 & 1)) {
        data_021cde64[0] = data_020decb4;
        data_021cde64[1] = data_020decac;
        data_021cde64[2] = data_020de95c;
        data_021cde64[3] = data_020dec9c;
        data_021cde64[4] = data_020dec94;
        data_021cde64[5] = data_020de89c;
        data_021cde64[6] = data_020de8a4;
        data_021cde64[7] = data_020dec7c;
        data_021cde64[8] = data_020dec74;
        data_021cde64[9] = data_020dec6c;
        data_021cde64[10] = data_020de93c;
        data_021cde64[11] = data_020dec5c;
        data_021cde64[12] = data_020dec54;
        data_021cde64[13] = data_020de92c;
        data_021cde64[14] = data_020de8bc;
        data_021cde64[15] = data_020dec3c;
        data_021cde64[16] = data_020de924;
        data_021cda64 |= 1;
    }
    PMF f;

    f = data_021cde64[obj->unk_3C];
    (obj->*f)();
}
