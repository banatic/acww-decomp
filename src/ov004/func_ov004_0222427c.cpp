/* func_ov004_0222427c @ 0x0222427c, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222427c {
    virtual void vfunc();
    char pad[0xB0 - 4];
    int field_at_B0;
};

typedef void (UnkStruct_0222427c::*PMF)();

struct PMFEntry {
    int func_or_offset;
    int adj_flags;
    char pad_08;
    char pad[3];
};

extern unsigned char data_ov004_02254620[];
extern PMFEntry data_ov004_02254618[];

extern "C" void func_ov004_0222427c(UnkStruct_0222427c *obj)
{
    int idx = obj->field_at_B0;
    int off = idx * 12;
    if (data_ov004_02254620[off] != 0) {
        PMFEntry *e = &data_ov004_02254618[idx];
        if (e->func_or_offset != 0) {
            (obj->*(*reinterpret_cast<PMF *>(&e->func_or_offset)))();
        }
    }
}
