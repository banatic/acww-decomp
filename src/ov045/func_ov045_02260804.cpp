/* func_ov045_02260804 @ 0x02260804, 0x44 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02260804 {
    virtual void vfunc();
    char pad[0xB0 - 4];
    int field_at_B0;
};

typedef void (UnkStruct_02260804::*PMF)();

struct PMFEntry {
    int func_or_offset;
    int adj_flags;
    char pad_08;
    char pad[3];
};

extern unsigned char data_ov045_022615ac[];
extern PMFEntry data_ov045_022615a4[];

extern "C" void func_ov045_02260804(UnkStruct_02260804 *obj)
{
    int idx = obj->field_at_B0;
    int off = idx * 12;
    if (data_ov045_022615ac[off] != 0) {
        PMFEntry *e = &data_ov045_022615a4[idx];
        if (e->func_or_offset != 0) {
            (obj->*(*reinterpret_cast<PMF *>(&e->func_or_offset)))();
        }
    }
}
