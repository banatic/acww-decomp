/* func_0209f6e4 @ 0x0209f6e4, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern void *data_020ccf94;
extern int func_0203e21c(void);
extern void *func_020682e0(int);
extern int func_020a12d4(void);
extern int func_020a12c0(void);
extern void func_020a8164(void *, const void *);
extern void func_02068340(void *, void *);
extern void func_0209f820(void *, int);
extern int func_02073d90(void *);
extern const char data_020e37e4[];
extern const char data_020e37d0[];
}

struct UnkStruct_0209f6e4 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

struct UnkStruct_0209f6e4_2 {
    char pad_00[0x54];
    UnkStruct_0209f6e4 sub;
    char pad_58[0x1a];
    unsigned char unk_72;
};

struct Res {
    char pad_00[8];
    int unk_08;
};

extern "C" void func_0209f6e4(UnkStruct_0209f6e4_2 *obj)
{
    Res *r;

    if (func_0203e21c() != 0) {
        r = (Res *) func_020682e0(0);
        obj->sub.v2();
        if (func_020a12d4() != 0 || func_020a12c0() != 0) {
            func_020a8164(&obj->sub, data_020e37e4);
            obj->unk_72 = 4;
        } else if (func_02073d90(data_020ccf94) != 0) {
            func_020a8164(&obj->sub, data_020e37d0);
            obj->unk_72 = 4;
        } else {
            func_020a8164(&obj->sub, data_020e37d0);
            obj->unk_72 = 0;
        }
        func_02068340(r, &obj->sub);
        r->unk_08 = 1;
        func_0209f820(obj, 2);
    } else {
        func_0209f820(obj, 0);
    }
}
