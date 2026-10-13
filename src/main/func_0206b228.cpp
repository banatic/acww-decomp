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

extern "C" void func_0206b228(UnkStruct_0206b228 *p)
{
    static PMF tbl[35] = {data_020deb94, data_020dea3c, data_020dea44, data_020deb7c, data_020deb74, data_020deb6c,
                          data_020dea64, data_020deb5c, data_020deb54, data_020dea7c, data_020dea84, data_020deb3c,
                          data_020deb34, data_020deb2c, data_020dea9c, data_020deb1c, data_020deb14, data_020deab4,
                          data_020deacc, data_020deadc, data_020deae4, data_020deaf4, data_020deafc, data_020deb0c,
                          data_020deb24, data_020deb4c, data_020deb84, data_020deba4, data_020debc4, data_020debd4,
                          data_020debe4, data_020dec0c, data_020dec2c, data_020dec34, data_020dec4c};
    PMF m = tbl[p->idx];
    (p->*m)();
}
