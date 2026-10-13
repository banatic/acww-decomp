/* func_0206ace4 @ 0x0206ace4, 0x180 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206ace4;
typedef void (UnkStruct_0206ace4::*PMF)(void);

struct UnkStruct_0206ace4 {
    unsigned char pad_00[0x3c];
    int unk_3C;
};

extern PMF data_020de8fc, data_020de90c, data_020de91c, data_020dea14, data_020dea1c, data_020dea24, data_020dea34,
    data_020dea4c, data_020dea5c, data_020dea6c, data_020dea74, data_020dea8c, data_020dea94, data_020deaa4, data_020deaac,
    data_020dead4, data_020deaec, data_020deb04, data_020deb44, data_020deb8c, data_020debcc;

extern "C" void func_0206ace4(UnkStruct_0206ace4 *obj)
{
    static PMF tbl[21] = {data_020de8fc, data_020de90c, data_020de91c, data_020dea14, data_020dea1c, data_020dea24,
                          data_020dea34, data_020dea4c, data_020dea5c, data_020dea6c, data_020dea74, data_020dea8c,
                          data_020dea94, data_020deaa4, data_020deaac, data_020dead4, data_020deaec, data_020deb04,
                          data_020deb44, data_020deb8c, data_020debcc};
    PMF f;

    f = tbl[obj->unk_3C];
    (obj->*f)();
}
