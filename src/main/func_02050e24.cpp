/* func_02050e24 @ 0x02050e24, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c81bc;
extern void *data_021c8194;

extern "C" void *NNS_FndGetNextListObject(void *a, int b);
extern "C" void NNS_FndRemoveListObject(void *a, void *obj);
extern "C" void func_020e993c(void *a, void *obj);

class UnkStruct_02050e24 {
  public:
    virtual void method0();
};

extern "C" void func_02050e24(void)
{
    while (1) {
        void *obj = NNS_FndGetNextListObject(&data_021c81bc, 0);
        if (obj == 0) {
            break;
        }
        NNS_FndRemoveListObject(&data_021c81bc, obj);
        ((UnkStruct_02050e24 *) obj)->method0();
        func_020e993c(data_021c8194, obj);
    }
}
