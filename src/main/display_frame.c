/* display_frame: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020540e4 @ 0x020540e4, 0x8c bytes, Thumb
 * func_020540c0 @ 0x020540c0, 0x24 bytes, Thumb
 * func_020540bc @ 0x020540bc, 0x2 bytes, Thumb
 * func_02054094 @ 0x02054094, 0x28 bytes, Thumb
 * func_02054090 @ 0x02054090, 0x2 bytes, Thumb
 * func_02054070 @ 0x02054070, 0x20 bytes, Thumb
 */

typedef struct UnkStruct_02054094 UnkStruct_02054094;

typedef void (*Method)(UnkStruct_02054094 *);

typedef struct VTable {
    Method method;
} VTable;

struct UnkStruct_02054094 {
    VTable *vtable;
};

typedef struct UnkStruct_02054070 UnkStruct_02054070;

typedef struct ObjVtbl ObjVtbl;

struct ObjVtbl {
    void (*unk_00)(UnkStruct_02054070 *);
    void (*unk_04)(UnkStruct_02054070 *);
};

struct UnkStruct_02054070 {
    ObjVtbl *vtbl;
};

extern void func_020e95f8(void);
extern void func_02041dc4(void);
extern void GX_SetBankForLCDC(unsigned int);
extern void MIi_CpuClearFast(unsigned int, unsigned int, unsigned int);
extern void func_02110aa0(void);
extern void func_02002ee8(void);
extern void func_020024cc(void);
extern void func_020b98dc(void);
extern void func_020b9990(void);
extern void func_0200240c(void);
extern void func_02002f68(void);
extern unsigned char data_021c8c9c[];
extern unsigned char data_021c8ca0[];
extern void func_020898e8(void);
extern void func_02002ec0(void);
extern void func_02002408(void);
extern void func_02041c28(void);

void func_020540c0(void);

void func_020540e4(void)
{
    volatile unsigned int v1;
    volatile unsigned int v0;
    volatile unsigned int v2;

    func_020e95f8();
    func_020540c0();
    func_02041dc4();

    *(volatile unsigned short *) 0x04000304 = (*(volatile unsigned short *) 0x04000304 & 0xfffffdf1) | 0x20e;

    GX_SetBankForLCDC(0x1f7);

    v0 = 0;
    MIi_CpuClearFast(v0, 0x06800000, 0x00084000);

    func_02110aa0();

    v1 = 0xc0;
    MIi_CpuClearFast(v1, 0x07000000, 0x00000400);

    v2 = 0;
    MIi_CpuClearFast(v2, 0x05000000, 0x00000400);

    func_02002ee8();
    func_020024cc();
    func_020b98dc();
    func_020b9990();
}

void func_020540c0(void)
{
    unsigned int *addr0;
    unsigned int *addr1;
    unsigned int value;

    addr0 = (unsigned int *) data_021c8ca0;
    addr1 = (unsigned int *) data_021c8c9c;
    value = 0;

    *addr0 = value;
    *addr1 = value;

    func_0200240c();
    func_02002f68();
}

void func_020540bc(void) {}

void func_02054094(void)
{
    func_020898e8();
    if ((*(UnkStruct_02054094 **) data_021c8ca0)) {
        (*(UnkStruct_02054094 **) data_021c8ca0)->vtable->method((*(UnkStruct_02054094 **) data_021c8ca0));
    }
    func_02002ec0();
    func_02002408();
}

void func_02054090(void) {}

void func_02054070(void)
{
    UnkStruct_02054070 *obj;
    obj = (*(UnkStruct_02054070 **) data_021c8ca0);
    if (obj) {
        obj->vtbl->unk_04(obj);
    }
    func_02041c28();
}
