/* func_ov003_0221a35c @ 0x0221a35c, 0x128 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0221a35c {
  public:
    virtual int vfunc_00();
    char pad_04[0x39c - 4];
    int unk_39C;
};

typedef int (UnkStruct_0221a35c::*PMF)();

extern PMF data_ov003_022381c0;
extern PMF data_ov003_02238228;
extern PMF data_ov003_02238190;
extern PMF data_ov003_02238188;
extern PMF data_ov003_02238238;
extern PMF data_ov003_02238270;
extern PMF data_ov003_02238268;
extern PMF data_ov003_02238260;
extern PMF data_ov003_02238258;
extern PMF data_ov003_02238250;
extern PMF data_ov003_02238248;
extern PMF data_ov003_02238240;
extern PMF data_ov003_02238208;
extern PMF data_ov003_02238230;

extern "C" int func_ov003_0221a35c(UnkStruct_0221a35c *self, int idx)
{
    static PMF arr[14] = {data_ov003_022381c0, data_ov003_02238228, data_ov003_02238190, data_ov003_02238188,
                          data_ov003_02238238, data_ov003_02238270, data_ov003_02238268, data_ov003_02238260,
                          data_ov003_02238258, data_ov003_02238250, data_ov003_02238248, data_ov003_02238240,
                          data_ov003_02238208, data_ov003_02238230};
    if (idx >= 14) {
        goto ret0;
    }
    if ((self->*arr[idx])()) {
        self->unk_39C = idx;
        return 1;
    }
ret0:
    return 0;
}
