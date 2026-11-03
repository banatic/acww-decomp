/* xct_exchange: 6 functions, module ov055
 * mwccarm 1.2/base -O4,s
 * func_ov055_02260544 @ 0x02260544, 0x5c bytes, Thumb
 * func_ov055_02260514 @ 0x02260514, 0x30 bytes, Thumb
 * func_ov055_022604f4 @ 0x022604f4, 0x20 bytes, Thumb
 * func_ov055_022604d4 @ 0x022604d4, 0x20 bytes, Thumb
 * func_ov055_02260478 @ 0x02260478, 0x5c bytes, Thumb
 * func_ov055_02260420 @ 0x02260420, 0x58 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x710];
    unsigned char unk_710;
    unsigned char pad_711[3];
    unsigned char unk_714[0x23C];
    unsigned char pad_950[0x818];
    unsigned char unk_1168;
} UnkStruct_02260544;

extern void func_020b1130(void);
extern int func_02090040(int a);
extern void MI_CpuCopy8(int a, void *b, int c);
extern void func_02090174(int a);
extern int func_020a145c(void);
extern char data_021d11c4;
extern char SDK_OVERLAY_ov067_ID;
extern void func_02077b9c(char *);
extern int func_02077b70(char *, int);
extern unsigned int SDK_OVERLAY_ov068_ID;
extern int func_02090020(void *);
extern char *func_020901a0(void *);
extern void *func_ov055_02260a40(void *);
extern int func_0202ee5c(void *);
extern void func_020edf54(void *);
extern char data_ov055_02260fd4[];

void func_ov055_02260544(UnkStruct_02260544 *p)
{
    int r;
    func_020b1130();
    r = func_02090040(4);
    MI_CpuCopy8(r, p->unk_714, 0x950);
    p->unk_1168 = 1;
    func_02090174(r);
    if (p->unk_710 == 0) {
        int t = func_020a145c();
        if (t == 1 || t == 4) {
            p->unk_710 = 1;
        }
    }
}

void func_ov055_02260514(void *self)
{
    int result;

    if (((unsigned char *) self)[0x710]) {
        return;
    }
    result = ((void) (func_02090040(4)), func_020a145c());
    if (result == 1 || result == 4) {
        ((unsigned char *) self)[0x710] = 1;
    }
}

void func_ov055_022604f4(void *receiver)
{
    func_02077b9c(&data_021d11c4);
    func_02077b70(&data_021d11c4, (int) &SDK_OVERLAY_ov067_ID);
}

void func_ov055_022604d4(void *receiver)
{
    func_02077b9c((char *) (((unsigned int *) &data_021d11c4)));
    func_02077b70((char *) (((unsigned int *) &data_021d11c4)), (int) (&SDK_OVERLAY_ov068_ID));
}

void *func_ov055_02260478(void *self)
{
    *(void **) self = (void *) data_ov055_02260fd4;
    func_02090020((char *) self + 0x1abc);
    func_020901a0((char *) self + 0x116c);
    func_02090020((char *) self + 0x1064);
    func_020901a0((char *) self + 0x714);
    func_ov055_02260a40((char *) self + 0x658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}

unsigned char *func_ov055_02260420(unsigned char *self)
{
    *(unsigned int *) self = (unsigned int) ((int *) data_ov055_02260fd4);
    func_02090020((void *) (self + 0x1abc));
    func_020901a0((void *) (self + 0x116c));
    func_02090020((void *) (self + 0x1064));
    func_020901a0((void *) (self + 0x714));
    func_ov055_02260a40((void *) (self + 0x658));
    func_0202ee5c((void *) self);
    return self;
}
