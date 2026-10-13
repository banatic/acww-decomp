/* func_ov107_0229cc14 @ 0x0229cc14, 0x94 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229cc14 {
  public:
    virtual void vfunc_00();
};

typedef void (UnkStruct_0229cc14::*PMF)();

extern "C" void func_ov107_0229d480(UnkStruct_0229cc14 *);
extern PMF data_ov107_0229e380, data_ov107_0229e2b0, data_ov107_0229e2a0, data_ov107_0229e2c8;
static unsigned int s_guard;
static PMF s_arr[4];

extern "C" void func_ov107_0229cc14(UnkStruct_0229cc14 *obj)
{
    if (((unsigned char *) obj)[0xbc] == 4) {
        func_ov107_0229d480(obj);
        return;
    }
    if (!(s_guard & 1)) {
        s_arr[0] = data_ov107_0229e380;
        s_arr[1] = data_ov107_0229e2b0;
        s_arr[2] = data_ov107_0229e2a0;
        s_arr[3] = data_ov107_0229e2c8;
        s_guard |= 1;
    }
    int idx = ((unsigned char *) obj)[0xbc];
    (obj->*(s_arr[idx]))();
}
