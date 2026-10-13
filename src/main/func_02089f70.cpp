/* func_02089f70 @ 0x02089f70, 0x56 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02089f70 {
  public:
    virtual void *vfunc_00();   // vtable slot 0
    virtual void *getB();       // vtable slot 1
    unsigned char pad_04[0x18]; // 0x04 .. 0x1c
    unsigned int unk_1C;        // 0x1c
    unsigned int unk_20;        // 0x20
};

extern "C" int func_02089f70(UnkStruct_02089f70 *a, UnkStruct_02089f70 *b)
{
    int flag = ((a->unk_1C & b->unk_20) != 0 && (a->unk_20 & b->unk_1C) != 0);
    if (flag) {
        void *v1 = a->getB();
        if (v1 != 0) {
            void *v2 = b->getB();
            if (v1 == v2) {
                return 0;
            }
        }
        if (a != b) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
