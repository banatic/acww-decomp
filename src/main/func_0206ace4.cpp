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

extern int data_021cda7c;
extern PMF data_021ce01c[21];

extern "C" void func_0206ace4(UnkStruct_0206ace4 *obj)
{
    if (!(data_021cda7c & 1)) {
        data_021ce01c[0] = data_020de8fc;
        data_021ce01c[1] = data_020de90c;
        data_021ce01c[2] = data_020de91c;
        data_021ce01c[3] = data_020dea14;
        data_021ce01c[4] = data_020dea1c;
        data_021ce01c[5] = data_020dea24;
        data_021ce01c[6] = data_020dea34;
        data_021ce01c[7] = data_020dea4c;
        data_021ce01c[8] = data_020dea5c;
        data_021ce01c[9] = data_020dea6c;
        data_021ce01c[10] = data_020dea74;
        data_021ce01c[11] = data_020dea8c;
        data_021ce01c[12] = data_020dea94;
        data_021ce01c[13] = data_020deaa4;
        data_021ce01c[14] = data_020deaac;
        data_021ce01c[15] = data_020dead4;
        data_021ce01c[16] = data_020deaec;
        data_021ce01c[17] = data_020deb04;
        data_021ce01c[18] = data_020deb44;
        data_021ce01c[19] = data_020deb8c;
        data_021ce01c[20] = data_020debcc;
        data_021cda7c |= 1;
    }
    PMF f;

    f = data_021ce01c[obj->unk_3C];
    (obj->*f)();
}
