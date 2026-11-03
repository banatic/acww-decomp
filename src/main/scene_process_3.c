/* scene_process_3: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b72f4 @ 0x020b72f4, 0x44 bytes, Thumb
 * func_020b72e4 @ 0x020b72e4, 0x10 bytes, Thumb
 * func_020b72e0 @ 0x020b72e0, 0x4 bytes, Thumb
 * func_020b72dc @ 0x020b72dc, 0x4 bytes, Thumb
 * func_020b72d8 @ 0x020b72d8, 0x4 bytes, Thumb
 * func_020b72d4 @ 0x020b72d4, 0x2 bytes, Thumb
 * func_020b72a4 @ 0x020b72a4, 0x30 bytes, Thumb
 * func_020b727c @ 0x020b727c, 0x28 bytes, Thumb
 * func_020b7238 @ 0x020b7238, 0x44 bytes, Thumb
 * func_020b7228 @ 0x020b7228, 0x10 bytes, Thumb
 * func_020b7218 @ 0x020b7218, 0x10 bytes, Thumb
 * func_020b71dc @ 0x020b71dc, 0x3c bytes, Thumb
 * func_020b7198 @ 0x020b7198, 0x44 bytes, Thumb
 * func_020b7130 @ 0x020b7130, 0x68 bytes, Thumb
 * func_020b70e8 @ 0x020b70e8, 0x48 bytes, Thumb
 */

typedef struct {
    volatile void *func;
    unsigned char pad_04[15];
    volatile unsigned char flags;
} UnkStruct_020b72f4;

typedef struct UnkStruct_020b7238 {
    void *vtable;
    char pad_04[15];
    unsigned char flags;
} UnkStruct_020b7238;

struct s_020b71dc {
    char pad_00[0x10];
    int unk_10;
    int unk_14;
};

extern void *func_020edf70(unsigned int size);
extern void *func_020ee660(void *);
extern unsigned char data_020da13c[];
extern unsigned char data_020e3c94[];
extern unsigned char data_020e5764[];
extern void func_0200471c(void);
extern void func_020ee62c(void *p);
extern void func_020edf54(void *p);
extern unsigned char data_020e5574[];
extern int SDK_OVERLAY_ov002_ID;
extern void func_0204f934(int);
extern void func_0204f8ec(int);
extern int data_020e54b4;
extern int data_020e54bc;
extern int data_021f6944;
extern unsigned char data_020e5538[];
extern unsigned int data_020e54f4[];
extern unsigned int data_020e54b8;
extern unsigned char data_020e54a8;
extern int data_020e5688[];
extern int data_020e54c0;

UnkStruct_020b72f4 *func_020b72f4(void)
{
    UnkStruct_020b72f4 *obj = (UnkStruct_020b72f4 *) func_020edf70(0x50);
    if (obj) {
        func_020ee660(obj);
        obj->func = (void *) data_020da13c;
        obj->func = (void *) data_020e3c94;
        obj->flags |= 1;
        obj->flags |= 4;
        obj->func = (void *) data_020e5764;
    }
    return obj;
}

int func_020b72e4(void)
{
    func_0200471c();
    return 1;
}

int func_020b72e0(void)
{
    return 1;
}

int func_020b72dc(void)
{
    return 1;
}

int func_020b72d8(void)
{
    return 1;
}

void func_020b72d4(void) {}

void *func_020b72a4(void *arg)
{
    *(volatile void **) arg = (void *) ((int *) data_020e5764);
    *(volatile void **) arg = (void *) ((int *) data_020e3c94);
    *(volatile void **) arg = (void *) ((int *) data_020da13c);
    func_020ee62c(arg);
    func_020edf54(arg);
    return arg;
}

void *func_020b727c(void *p)
{
    void *val;
    val = (void *) data_020e5764;
    *(void *volatile *) p = val;
    val = (void *) data_020e3c94;
    *(void *volatile *) p = val;
    val = (void *) data_020da13c;
    *(void *volatile *) p = val;
    func_020ee62c(p);
    return p;
}

void *func_020b7238(void)
{
    UnkStruct_020b7238 *obj;
    obj = func_020edf70(0x50);
    if (obj) {
        func_020ee660(obj);
        obj->vtable = (void *) data_020da13c;
        obj->vtable = (void *) data_020e3c94;
        obj->flags |= 1;
        obj->flags |= 4;
        obj->vtable = (void *) data_020e5574;
    }
    return obj;
}

void func_020b7228(void)
{
    func_0204f934((int) &SDK_OVERLAY_ov002_ID);
}

void func_020b7218(void)
{
    func_0204f8ec((int) &SDK_OVERLAY_ov002_ID);
}

void func_020b71dc(struct s_020b71dc *p)
{
    int x = p->unk_10;
    data_020e54b4 = x;
    data_020e54bc = p->unk_14;
    if (x != -1) {
        func_0204f934(x);
    }
    if (data_020e54bc != -1) {
        func_0204f934(data_020e54bc);
    }
}

void func_020b7198(void)
{
    if (data_020e54b4 != -1) {
        func_0204f8ec(data_020e54b4);
        data_020e54b4 = -1;
    }
    if (data_020e54bc != -1) {
        func_0204f8ec(data_020e54bc);
        data_020e54bc = -1;
    }
}

void func_020b7130(void)
{
    unsigned char c;
    unsigned int w;

    c = data_020e5538[data_021f6944];
    w = data_020e54f4[c];
    func_0204f934(w);
    data_020e54b8 = w;
    data_020e54a8 = c;

    if (data_020e5688[data_021f6944] != -1) {
        func_0204f934(data_020e5688[data_021f6944]);
        data_020e54c0 = data_020e5688[data_021f6944];
    }
}

void func_020b70e8(void)
{
    func_020b7198();
    if (data_020e54c0 != -1) {
        func_0204f8ec(data_020e54c0);
        data_020e54c0 = -1;
    }
    if ((*(int *) &data_020e54b8) != -1) {
        func_0204f8ec((*(int *) &data_020e54b8));
        (*(int *) &data_020e54b8) = -1;
    }
}
