/* func_ov125_0229faf8 @ 0x0229faf8, 0x24 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229faf8 {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
};

extern "C" void func_ov002_0220a374(UnkStruct_0229faf8 *, int);

extern "C" void func_ov125_0229faf8(void *p)
{
    func_ov002_0220a374((UnkStruct_0229faf8 *) ((char *) p + 0x644), 0);
    ((UnkStruct_0229faf8 *) ((char *) p + 0x644))->vf3();
}
