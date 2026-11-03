/* room_object: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220c648 @ 0x0220c648, 0x70 bytes, Thumb
 * func_ov004_0220c640 @ 0x0220c640, 0x8 bytes, Thumb
 * func_ov004_0220c5cc @ 0x0220c5cc, 0x74 bytes, Thumb
 * func_ov004_0220c5c8 @ 0x0220c5c8, 0x4 bytes, Thumb
 * func_ov004_0220c560 @ 0x0220c560, 0x68 bytes, Thumb
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned char pad_0C[0x3F4];
} UnkStruct_0220c5cc;

typedef struct {
    char pad_00[0x150];
    UnkStruct_0220c5cc sub;
    char pad_550[0x220];
    unsigned short unk_770;
} RoomObject;

extern int func_020e895c(void *dst, int c, int n);
extern void func_020ee470(void *self);
extern void func_ov004_0220fefc(void *self, void *local);
extern int func_ov004_0220e61c(void *self, void *local);
extern int func_ov004_0220c6b8(void *parameter0);
extern int func_ov004_0220ccf8(void *obj, int arg);
extern int func_ov004_0220fde0(void *ptr);
extern int func_02053690(int a);
extern int FX_Div(int a, unsigned int b);

void func_ov004_0220c648(void *self)
{
    char local[0x10];
    int *p150;
    int *p158;

    p150 = (int *) ((char *) self + 0x150);
    p158 = (int *) ((char *) self + 0x158);

    func_020e895c((char *) self + 0x150, 0, 0x400);

    *p158 = *p150;
    *((int *) ((char *) self + 0x154)) = *p158;

    if (*p150 == 0) {
        func_020ee470(self);
    }

    if (*(unsigned short *) ((char *) self + 0x770) == 1) {
        func_ov004_0220fefc(self, local);
        func_ov004_0220e61c(self, local);
    }

    (*(unsigned short *) ((char *) self + 0x770))++;
}

int func_ov004_0220c640(void *arg0)
{
    return func_ov004_0220c6b8((void *) arg0);
}

void func_ov004_0220c5cc(RoomObject *obj)
{
    func_020e895c(&obj->sub, 0, sizeof(obj->sub));
    obj->sub.unk_08 = obj->sub.unk_00;
    obj->sub.unk_04 = obj->sub.unk_08;
    if (obj->sub.unk_00 == 0) {
        func_ov004_0220ccf8(obj, 7);
    } else {
        if (obj->unk_770 == 1) {
            char local[16];
            func_ov004_0220fefc(obj, local);
            func_ov004_0220e61c(obj, local);
        }
    }
    obj->unk_770++;
}

int func_ov004_0220c5c8(void *callbackObject)
{
    return 1;
}

void func_ov004_0220c560(void *ptr)
{
    unsigned int field;
    short tmp;
    int res;

    field = *(unsigned int *) ((char *) ptr + 0x780);
    if (field != 0x23 && field != 0x24 && field != 0x25) {
        tmp = *(short *) ((char *) ptr + 0x8e);
        tmp += 0x400;
        *(short *) ((char *) ptr + 0x8e) = tmp;
    }

    res = FX_Div(func_02053690(func_ov004_0220fde0(ptr)), 0x64000);
    res >>= 2;
    *(int *) ((char *) ptr + 0x158) = res;
    *(int *) ((char *) ptr + 0x154) = *(int *) ((char *) ptr + 0x158);
    *(int *) ((char *) ptr + 0x150) = *(int *) ((char *) ptr + 0x154);
}
