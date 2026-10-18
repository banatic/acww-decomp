/* func_0206cf3c @ 0x0206cf3c, 0x250 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0206cf3c {
  public:
    int pad_00[14];
    int idx;
};

typedef void (UnkStruct_0206cf3c::*PMF)(void);

extern PMF data_020deee4, data_020de8e4, data_020de834, data_020dec84, data_020dec8c, data_020deeec, data_020debdc,
    data_020de874, data_020de8ec, data_020de8f4;
extern PMF data_020dec24, data_020def04, data_020def14, data_020def0c, data_020dec44, data_020deefc, data_020deef4,
    data_020decbc, data_020decc4, data_020deedc;
extern PMF data_020deed4, data_020deecc, data_020decf4, data_020deebc, data_020deeb4, data_020deeac, data_020ded2c,
    data_020dee9c, data_020dee94, data_020ded54;
extern PMF data_020ded84, data_020dee7c, __ptmf_null, data_020dee74, data_020dedb4;

extern "C" void func_0206cf3c(UnkStruct_0206cf3c *p);

extern int data_021cda44;
extern PMF data_021ce1dc[35];

extern "C" void func_0206cf3c(UnkStruct_0206cf3c *p)
{
    if (!(data_021cda44 & 1)) {
        data_021ce1dc[0] = data_020deee4;
        data_021ce1dc[1] = data_020de8e4;
        data_021ce1dc[2] = data_020de834;
        data_021ce1dc[3] = data_020dec84;
        data_021ce1dc[4] = data_020dec8c;
        data_021ce1dc[5] = data_020deeec;
        data_021ce1dc[6] = data_020debdc;
        data_021ce1dc[7] = data_020de874;
        data_021ce1dc[8] = data_020de8ec;
        data_021ce1dc[9] = data_020de8f4;
        data_021ce1dc[10] = data_020dec24;
        data_021ce1dc[11] = data_020def04;
        data_021ce1dc[12] = data_020def14;
        data_021ce1dc[13] = data_020def0c;
        data_021ce1dc[14] = data_020dec44;
        data_021ce1dc[15] = data_020deefc;
        data_021ce1dc[16] = data_020deef4;
        data_021ce1dc[17] = data_020decbc;
        data_021ce1dc[18] = data_020decc4;
        data_021ce1dc[19] = data_020deedc;
        data_021ce1dc[20] = data_020deed4;
        data_021ce1dc[21] = data_020deecc;
        data_021ce1dc[22] = data_020decf4;
        data_021ce1dc[23] = data_020deebc;
        data_021ce1dc[24] = data_020deeb4;
        data_021ce1dc[25] = data_020deeac;
        data_021ce1dc[26] = data_020ded2c;
        data_021ce1dc[27] = data_020dee9c;
        data_021ce1dc[28] = data_020dee94;
        data_021ce1dc[29] = data_020ded54;
        data_021ce1dc[30] = data_020ded84;
        data_021ce1dc[31] = data_020dee7c;
        data_021ce1dc[32] = __ptmf_null;
        data_021ce1dc[33] = data_020dee74;
        data_021ce1dc[34] = data_020dedb4;
        data_021cda44 |= 1;
    }
    PMF m = data_021ce1dc[p->idx];
    if (m) {
        (p->*m)();
    }
}
