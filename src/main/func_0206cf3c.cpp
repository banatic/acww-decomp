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

extern "C" void func_0206cf3c(UnkStruct_0206cf3c *p)
{
    static PMF tbl[35] = {data_020deee4, data_020de8e4, data_020de834, data_020dec84, data_020dec8c, data_020deeec,
                          data_020debdc, data_020de874, data_020de8ec, data_020de8f4, data_020dec24, data_020def04,
                          data_020def14, data_020def0c, data_020dec44, data_020deefc, data_020deef4, data_020decbc,
                          data_020decc4, data_020deedc, data_020deed4, data_020deecc, data_020decf4, data_020deebc,
                          data_020deeb4, data_020deeac, data_020ded2c, data_020dee9c, data_020dee94, data_020ded54,
                          data_020ded84, data_020dee7c, __ptmf_null,   data_020dee74, data_020dedb4};
    PMF m = tbl[p->idx];
    if (m) {
        (p->*m)();
    }
}
