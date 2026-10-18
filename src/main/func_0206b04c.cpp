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

extern int data_021cda70;
extern PMF data_021cddf4[14];

extern "C" void func_0206b04c(UnkStruct_0206b04c *obj)
{
    if (!(data_021cda70 & 1)) {
        data_021cddf4[0] = data_020dee34;
        data_021cddf4[1] = data_020dee4c;
        data_021cddf4[2] = data_020dee64;
        data_021cddf4[3] = data_020dee8c;
        data_021cddf4[4] = data_020dea04;
        data_021cddf4[5] = data_020de9fc;
        data_021cddf4[6] = data_020de9f4;
        data_021cddf4[7] = data_020de80c;
        data_021cddf4[8] = data_020dedbc;
        data_021cddf4[9] = data_020de9dc;
        data_021cddf4[10] = data_020de9d4;
        data_021cddf4[11] = data_020de824;
        data_021cddf4[12] = data_020de9c4;
        data_021cddf4[13] = data_020de9bc;
        data_021cda70 |= 1;
    }
    PMF f;

    f = data_021cddf4[obj->idx];
    (obj->*f)();
}
