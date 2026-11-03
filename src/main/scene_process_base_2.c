/* scene_process_base_2: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a56d4 @ 0x020a56d4, 0x3c bytes, Thumb
 * func_020a5670 @ 0x020a5670, 0x64 bytes, Thumb
 * func_020a55dc @ 0x020a55dc, 0x94 bytes, Thumb
 * func_020a5598 @ 0x020a5598, 0x44 bytes, Thumb
 * func_020a5580 @ 0x020a5580, 0x18 bytes, Thumb
 * func_020a553c @ 0x020a553c, 0x44 bytes, Thumb
 */

typedef struct {
    void *volatile vtbl;
    unsigned char pad_04[15];
    volatile unsigned char flags;
} UnkStruct_020a56d4;

struct UnkStruct_020a55dc {
    unsigned char pad_00[0x64];
    int unk_64;
};

extern void *func_020edf70(unsigned int size);
extern void *func_020ee660(void *obj);
extern int data_020da13c;
extern int data_020e3c94;
extern void func_02053f20(void);
extern void G3X_Init(void);
extern void GX_SetBankForBG(int arg);
extern void GX_SetBankForOBJ(int arg);
extern void GX_SetBankForBGExtPltt(int arg);
extern void GX_SetBankForTex(int arg);
extern void GX_SetBankForTexPltt(int arg);
extern void func_02002f68(void);
extern int func_020ee61c(void);
extern void func_0208f8f0(void);
extern void func_020a7448(void);
extern void func_020a6d84(void);
extern int func_02073dd4(struct UnkStruct_020a55dc *, int);
extern int func_020a6ea0(void);
extern void func_020a6eb0(int);
extern unsigned char data_021f42f0;
extern int data_021f42f4;
extern unsigned char data_021f42e0;
extern unsigned char data_021f42dc;
extern unsigned char data_021f42e4;
extern struct UnkStruct_020a55dc *data_020ccf94;
extern void func_02041a9c(void);
extern void func_02074904(int);
extern void func_020a6c08(void);
extern void func_02046600(void);
extern void func_0203de64(void);
extern void func_0202f144(int, int);
extern int func_020ee550(void *);
extern void func_0209dad0(void);
extern void func_020046c4(void);
extern void func_020ee4d8(int, int);
extern unsigned char data_020e3c7c;
extern unsigned char data_021dc6c4;

void *func_020a56d4(void)
{
    UnkStruct_020a56d4 *p = (UnkStruct_020a56d4 *) func_020edf70(0x50);
    if (p) {
        func_020ee660(p);
        p->vtbl = (void *) &data_020da13c;
        p->vtbl = (void *) &data_020e3c94;
        p->flags |= 1;
        p->flags |= 4;
    }
    return p;
}

void func_020a5670(void)
{
    func_02053f20();
    G3X_Init();
    GX_SetBankForBG(0x20);
    GX_SetBankForOBJ(0x1);
    GX_SetBankForBGExtPltt(0x40);
    GX_SetBankForTex(0x6);
    GX_SetBankForTexPltt(0x10);
    *(volatile unsigned int *) 0x040004c8 = 0x20000000;
    *(volatile unsigned int *) 0x040004cc = 0x00007fff;
    *(volatile unsigned int *) 0x040004c0 = 0x00007fff;
    *(volatile unsigned int *) 0x040004c4 = 0x0;
    func_02002f68();
}

int func_020a55dc(int arg)
{
    if (func_020ee61c() == 0) {
        return 0;
    }

    if (data_021f42f0 != 0) {
        return 1;
    }

    func_020a5670();
    func_0208f8f0();
    data_021f42f4 = arg;
    data_021f42e0 = 4;
    func_020a7448();
    func_020a6d84();
    data_021f42f0++;

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        int v = func_020a6ea0();
        switch (v) {
            case 6:
                func_020a6eb0(7);
                break;
            case 0xd:
                func_020a6eb0(0xe);
                break;
        }
    }

    data_021f42dc = 0;
    data_021f42e4 = 0;

    return 1;
}

void func_020a5598(int r0, int r1)
{
    int r5 = r0;
    int r4 = r1;
    if (r4 == 2) {
        data_021f42f0 = 0;
        if (*(unsigned short *) (r5 + 0xc) != 6) {
            func_02041a9c();
        }
        func_02074904(0);
        func_020a6c08();
        func_02046600();
        func_0203de64();
    }
    func_0202f144(r5, r4);
}

int func_020a5580(void *argument0)
{
    int result;
    if (func_020ee550((void *) argument0) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

void func_020a553c(int arg0, int arg1)
{
    if (arg1 == 2) {
        data_020e3c7c = 0;
        if (data_021dc6c4 != 0) {
            func_0209dad0();
        }
        data_021f42f4 = 0;
        func_020046c4();
    }
    func_020ee4d8(arg0, arg1);
}
