/* func_ov048_022616c0 @ 0x022616c0, 0x44 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022616c0 {
  public:
    char pad_00[0xB4];
    int index;
};

typedef void (UnkStruct_022616c0::*Pmf)();

struct PmfEntry {
    Pmf pmf;
    int pad_08;
};

extern unsigned char data_ov048_0226434c[];
extern PmfEntry data_ov048_02264344[];

extern "C" void func_ov048_022616c0(UnkStruct_022616c0 *obj)
{
    int off = obj->index * 12;
    if (data_ov048_0226434c[off] != 0) {
        return;
    }
    PmfEntry *e = (PmfEntry *) ((char *) data_ov048_02264344 + off);
    if (e->pmf == 0) {
        return;
    }
    (obj->*(e->pmf))();
}
