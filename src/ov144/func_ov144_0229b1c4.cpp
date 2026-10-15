/* func_ov144_0229b1c4 @ 0x0229b1c4, 0x90 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_0206fe54(void);
extern "C" void func_ov002_02209eb8(void *);
extern "C" int func_ov144_02299680(void *, int);
extern "C" int func_ov002_02207f60(void *);
extern "C" void func_ov002_0220ad18(void *, int);
extern "C" void func_02088df8(int, void *, int, void *, int, int, int, int, int, int, int, int);

class UnkStruct_0229b1c4_2 {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
};

struct UnkStruct_0229b1c4 {
    char pad_00[0x94];
    void *bufPtr;
    char pad_98[0x0C];
    int count;
    char pad_A8[0x80];
    UnkStruct_0229b1c4_2 obj;
};

extern unsigned char data_ov144_0229b3b0[];

extern "C" int func_ov144_0229b1c4(UnkStruct_0229b1c4 *s)
{
    int zero = 0;
    int neg1 = ~zero;
    int one = 1;
    int big = 0x1000;
    void *p4;
    if (func_0206fe54()) {
        func_ov002_02209eb8((char *) s + 0xC4);
    }
    if (!func_ov144_02299680(s, 1)) {
        return 0;
    }
    func_ov002_0220ad18((char *) s + 0x170, func_ov002_02207f60(s));
    p4 = (char *) s->bufPtr + 0x60;
    if (s->count > 0) {
        s->obj.f2();
        func_02088df8(one, (void *) data_ov144_0229b3b0, 0x80, p4, neg1, one, big, big, zero, neg1, zero, zero);
    }
    return 1;
}
