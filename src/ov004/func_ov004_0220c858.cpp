/* func_ov004_0220c858 @ 0x0220c858, 0xd8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct OV004Obj OV004Obj;

struct OV004Obj {
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
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void vf(int flag);

    char pad_04[0x8e - 0x4];
    short unk_8E;
    char pad_90[0x16c - 0x90];
    short unk_16C;
    char pad_16E[0x18c - 0x16e];
    char unk_18C;
    char pad_18D[0x288 - 0x18d];
    unsigned char unk_288;
    char pad_289[0x788 - 0x289];
    unsigned int unk_788;
};

typedef struct Pair {
    unsigned int x;
    unsigned int y;
} Pair;

extern "C" char *func_ov004_0220db94(void *ptr);
extern "C" void func_ov004_0220f27c(OV004Obj *self, void *ptr, int a, int b);
extern "C" void *func_ov004_0223cd50(void);
extern "C" Pair *func_ov004_0220db5c(void *ptr, unsigned int idx);
extern "C" OV004Obj *func_ov004_0223cc10(void *p, unsigned int a, unsigned int b, int c);
extern "C" unsigned int func_ov004_0220db68(void *ptr);
extern "C" void func_ov004_0220db90(void *ptr);
extern "C" int func_020e8870(void *addr, int val, int param);
extern "C" int func_ov004_0220ccf8(OV004Obj *self, int v);
extern "C" void func_ov004_0220d4ec(void *addr, OV004Obj *self);

extern "C" void func_ov004_0220c858(OV004Obj *self)
{
    short diff;
    int flag;
    void *p;
    char local[0x28];
    unsigned int i;
    Pair *a;
    Pair *b;
    OV004Obj *res;
    OV004Obj *s;

    diff = (short) (self->unk_16C - self->unk_8E);
    flag = diff < 0 ? 1 : 0;

    s = self;
    s->vf(flag);

    if (self->unk_288 == 0 && self->unk_788 == 1) {
        func_ov004_0220db94(local);
        func_ov004_0220f27c(self, local, 0, 0);

        for (i = 0; i < func_ov004_0220db68(local); i++) {
            p = func_ov004_0223cd50();
            a = func_ov004_0220db5c(local, i);
            b = func_ov004_0220db5c(local, i);
            res = func_ov004_0223cc10(p, a->x, b->y, 1);
            if (res != 0) {
                res->vf(flag);
            }
        }

        func_ov004_0220db90(local);
    }

    if (func_020e8870(&self->unk_8E, self->unk_16C, 0x700)) {
        func_ov004_0220ccf8(self, 1);
        func_ov004_0220d4ec(&self->unk_18C, self);
    }
}