/* func_ov052_0226194c @ 0x0226194c, 0x4c bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern "C" {

struct UnkStruct_0226194c {
    unsigned char pad_00[0x654];
    int m_index;
};

typedef int (UnkStruct_0226194c::*PMF)();

struct CheckEntry {
    void *ptr;
    int pad_04[3];
};

struct PMEntry {
    int pad_00[2];
    PMF pm;
};

extern CheckEntry data_ov052_02262008[];
extern PMEntry data_ov052_02262000[];

int func_ov052_0226194c(UnkStruct_0226194c *obj)
{
    int ret = 0;
    int idx = obj->m_index;
    if (data_ov052_02262008[idx].ptr != 0) {
        ret = (obj->*data_ov052_02262000[idx].pm)();
    }
    return ret;
}

} // extern "C"
