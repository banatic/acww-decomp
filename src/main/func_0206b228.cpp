/* func_0206b228 @ 0x0206b228, 0x24c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0206b228 {
  public:
    int pad_00[15];
    int idx;
};

typedef void (UnkStruct_0206b228::*PMF)(void);

extern PMF data_020deb94, data_020dea3c, data_020dea44, data_020deb7c, data_020deb74, data_020deb6c, data_020dea64,
    data_020deb5c, data_020deb54, data_020dea7c;
extern PMF data_020dea84, data_020deb3c, data_020deb34, data_020deb2c, data_020dea9c, data_020deb1c, data_020deb14,
    data_020deab4, data_020deacc, data_020deadc;
extern PMF data_020deae4, data_020deaf4, data_020deafc, data_020deb0c, data_020deb24, data_020deb4c, data_020deb84,
    data_020deba4, data_020debc4, data_020debd4;
extern PMF data_020debe4, data_020dec0c, data_020dec2c, data_020dec34, data_020dec4c;

extern "C" void func_0206b228(UnkStruct_0206b228 *p);

extern int data_021cda50;
extern PMF data_021ce0c4[35];

extern "C" void func_0206b228(UnkStruct_0206b228 *p)
{
    if (!(data_021cda50 & 1)) {
        data_021ce0c4[0] = data_020deb94;
        data_021ce0c4[1] = data_020dea3c;
        data_021ce0c4[2] = data_020dea44;
        data_021ce0c4[3] = data_020deb7c;
        data_021ce0c4[4] = data_020deb74;
        data_021ce0c4[5] = data_020deb6c;
        data_021ce0c4[6] = data_020dea64;
        data_021ce0c4[7] = data_020deb5c;
        data_021ce0c4[8] = data_020deb54;
        data_021ce0c4[9] = data_020dea7c;
        data_021ce0c4[10] = data_020dea84;
        data_021ce0c4[11] = data_020deb3c;
        data_021ce0c4[12] = data_020deb34;
        data_021ce0c4[13] = data_020deb2c;
        data_021ce0c4[14] = data_020dea9c;
        data_021ce0c4[15] = data_020deb1c;
        data_021ce0c4[16] = data_020deb14;
        data_021ce0c4[17] = data_020deab4;
        data_021ce0c4[18] = data_020deacc;
        data_021ce0c4[19] = data_020deadc;
        data_021ce0c4[20] = data_020deae4;
        data_021ce0c4[21] = data_020deaf4;
        data_021ce0c4[22] = data_020deafc;
        data_021ce0c4[23] = data_020deb0c;
        data_021ce0c4[24] = data_020deb24;
        data_021ce0c4[25] = data_020deb4c;
        data_021ce0c4[26] = data_020deb84;
        data_021ce0c4[27] = data_020deba4;
        data_021ce0c4[28] = data_020debc4;
        data_021ce0c4[29] = data_020debd4;
        data_021ce0c4[30] = data_020debe4;
        data_021ce0c4[31] = data_020dec0c;
        data_021ce0c4[32] = data_020dec2c;
        data_021ce0c4[33] = data_020dec34;
        data_021ce0c4[34] = data_020dec4c;
        data_021cda50 |= 1;
    }
    PMF m = data_021ce0c4[p->idx];
    (p->*m)();
}
