/* func_ov045_022607b4 @ 0x022607b4, 0x50 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022607b4 {
  public:
    virtual void vfunc_00();
    char pad_04[0xac];
    int unk_B0;
};

typedef void (UnkStruct_022607b4::*PMF)();

extern unsigned char data_ov045_022615ac[];
extern char data_ov045_022615a4[];
extern "C" void func_ov045_022607ac(UnkStruct_022607b4 *, int);

extern "C" void func_ov045_022607b4(UnkStruct_022607b4 *self)
{
    int off = self->unk_B0 * 12;
    if (data_ov045_022615ac[off] != 0) {
        return;
    }
    PMF *pmf_ptr = (PMF *) (data_ov045_022615a4 + off);
    if (*(int *) pmf_ptr == 0) {
        return;
    }
    (self->*(*pmf_ptr))();
    func_ov045_022607ac(self, 0);
}
