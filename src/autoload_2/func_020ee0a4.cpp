/* func_020ee0a4 @ 0x020ee0a4, 0x280 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct Blk Blk;

struct Blk {
    void *unk_00;
    int unk_04;
    unsigned int unk_08;
};

class UnkStruct_020ee0a4 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual int v15();
    unsigned char pad_04[0x4c - 4];
    Blk *unk_4C;
};

extern "C" Blk *func_020e99d8(unsigned int, void *);
extern "C" int func_020e9ed4(Blk *, int, int);
extern "C" void func_020e9974(void);
extern "C" void func_020e9fd4(Blk *);
extern "C" unsigned int func_020e9e34(void *);
extern "C" int func_020e9abc(Blk *);
extern "C" void func_020ee470(UnkStruct_020ee0a4 *);

extern "C" int func_020ee0a4(UnkStruct_020ee0a4 *self, unsigned int size, void *heap)
{
    Blk *cur;
    unsigned int end;
    Blk *alt;
    unsigned int room;
    int ok;
    int flag;
    // ENDDECLS

    cur = 0;
    if (self->unk_4C != 0) {
        return 1;
    }

    if (size == 0) {
        goto L_188;
    }
    cur = func_020e99d8(size, heap);
    if (cur == 0) {
        goto L_188;
    }

    flag = cur->unk_04 & 0x10;
    if (flag != 0) {
        func_020e9ed4(cur, 0x10, 0x10);
    }
    ok = self->v15();
    if (flag == 0) {
        if (func_020e9ed4(cur, 0x10, 0x10) == 0) {
            ok = 0;
        }
    }
    func_020e9974();
    if (ok == 0) {
        func_020e9fd4(cur);
        cur = 0;
        goto L_188;
    }
    end = cur->unk_08;
    end = end - func_020e9e34(cur);
    end = (end + 0x1f) & ~0x1f;
    if (size != end) {
        goto L_188;
    }
    func_020e9abc(cur);
    self->unk_4C = cur;
    return 1;

L_188:
    if (cur != 0) {
        goto L_22c;
    }
    cur = func_020e99d8(0xffffffff, heap);
    flag = cur->unk_04 & 0x10;
    if (flag != 0) {
        func_020e9ed4(cur, 0x10, 0x10);
    }
    ok = self->v15();
    if (flag == 0) {
        if (func_020e9ed4(cur, 0x10, 0x10) == 0) {
            ok = 0;
        }
    }
    func_020e9974();
    if (ok == 0) {
        func_020e9fd4(cur);
        func_020ee470(self);
        return 0;
    }
    end = cur->unk_08;
    end = end - func_020e9e34(cur);
    end = (end + 0x1f) & ~0x1f;

L_22c:
    if (cur == 0) {
        goto L_310;
    }
    room = cur->unk_08;
    alt = 0;
    room = room - func_020e9e34(cur);
    if ((((room + 0xf) & ~0xf) + 0x30) < func_020e9e34(heap)) {
        alt = func_020e99d8(end, heap);
    }
    if (alt != 0) {
        if (alt < cur) {
            func_020e9fd4(cur);
            cur = 0;
            ok = self->v15();
            func_020e9974();
            if (ok == 0) {
                func_020e9fd4(alt);
                alt = 0;
            }
        } else {
            func_020e9974();
            func_020e9fd4(alt);
            alt = 0;
        }
    }
    if (alt != 0) {
        func_020e9abc(alt);
        self->unk_4C = alt;
        return 1;
    }
    if (cur != 0) {
        func_020e9abc(cur);
        self->unk_4C = cur;
        return 1;
    }
L_310:
    func_020ee470(self);
    return 0;
}
