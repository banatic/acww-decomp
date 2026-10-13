/* func_020a8fb8 @ 0x020a8fb8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020a8fb8 {
  public:
    virtual void virtual0();
};

extern "C" void NNS_FndRemoveListObject(void *a, UnkStruct_020a8fb8 *b);
extern "C" void func_020e993c(int a, UnkStruct_020a8fb8 *b);
extern int data_021c81bc;
extern int data_021c8194;

extern "C" void func_020a8fb8(UnkStruct_020a8fb8 *p)
{
    if (p) {
        NNS_FndRemoveListObject(&data_021c81bc, p);
        p->virtual0();
        func_020e993c(data_021c8194, p);
    }
}
