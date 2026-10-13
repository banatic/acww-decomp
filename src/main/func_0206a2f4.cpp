/* func_0206a2f4 @ 0x0206a2f4, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
struct UnkStruct_0206a2f4 {
    unsigned char pad_00[0x24];
    void *unk_24;
};

class UnkStruct_0206a2f4_2 {
  public:
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
};

extern UnkStruct_0206a2f4_2 *func_02068034(void *);
extern void func_020a9334(struct UnkStruct_0206a2f4 *, int);
extern void func_020a7994(void *, int);

void func_0206a2f4(struct UnkStruct_0206a2f4 *p)
{
    int v1 = func_02068034(p->unk_24)->m3();
    func_020a9334(p, v1);

    int v2 = func_02068034(p->unk_24)->m3();
    func_020a7994((char *) p->unk_24 + 0x1a58, v2);

    *(int *) ((char *) p->unk_24 + 0x1a60) = 1;
}
}
