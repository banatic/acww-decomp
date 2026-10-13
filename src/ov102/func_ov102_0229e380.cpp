/* func_ov102_0229e380 @ 0x0229e380, 0x90 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_ov002_02207f48(void *p, int a);
extern "C" void func_ov002_022080a0(void *p, int a);
extern "C" void func_ov102_0229d740(void *p);
extern "C" void func_ov102_0229c288(void *p, int a);
extern "C" int func_0206fe54(int a);
extern "C" void func_0208e4c0(void *p, int a);
extern "C" void func_ov102_0229cd38(void *p);
extern "C" void func_ov002_02208098(void *p, int a);
extern "C" void func_ov002_02207e80(void *p, int a, int b, int c);
extern "C" int func_ov002_02207f60(void *p);

class UnkStruct_0229e380 {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
};

typedef struct UnkStruct_0229e380_2 {
    char pad_00[0x2274];
    char pad_2274[0x24d4 - 0x2274];
    int unk_24D4;
    char pad_24D8[0x259f - 0x24d8];
    unsigned char unk_259F;
    char pad_25A0[0x25a5 - 0x25a0];
    unsigned char unk_25A5;
} UnkStruct_0229e380_2;

extern "C" void func_ov102_0229e380(UnkStruct_0229e380_2 *p)
{
    if (func_ov002_02207f48(p, 0) != 0) {
        func_ov002_022080a0(p, 2);
        func_ov102_0229d740(p);
        func_ov102_0229c288(p, 0x40);
        unsigned char f = p->unk_259F;
        if (f != 0) {
            if (func_0206fe54(f) != 0) {
                unsigned char b = p->unk_25A5;
                if (b < 0x1e || b > 0x23) {
                    func_0208e4c0((void *) ((char *) p + 0x2274), 4);
                }
                UnkStruct_0229e380 *ptr = (UnkStruct_0229e380 *) ((char *) p + 0x2274);
                ptr->vf3();
                func_ov102_0229cd38(p);
                func_ov002_02208098(p, 4);
            }
        }
    }
    func_ov002_02207e80(p, 4, 0, 0);
    p->unk_24D4 = func_ov002_02207f60(p);
}
