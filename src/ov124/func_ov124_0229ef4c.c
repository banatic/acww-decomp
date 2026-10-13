/* func_ov124_0229ef4c @ 0x0229ef4c, 0x1a0 bytes, Thumb, module ov124
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x6c];
    unsigned char unk_6C;
    unsigned char pad_6D[0x7b];
    unsigned char unk_E8;
    unsigned char unk_E9;
} UnkStruct_0229ef4c;

extern void *data_021fbe94;
extern void *data_ov124_0229f4a0[];
extern const unsigned char data_ov124_0229f5d0[];
extern const unsigned char data_ov124_0229f610[];

extern void *func_02064b2c(void *a, void *b, int c, void *d);
extern void func_02002a88(void *a, int b, int c, int d, int e);
extern void func_02002cd8(const void *a, void *b, int c, int d, int e);
extern void func_ov002_0220b36c(void *self, const void *data, int a, int b);
extern void func_ov002_0220b318(void *self, int a);
extern __arm void func_020e993c(void *a, void *b);
extern int func_0206fca4(void);

void func_ov124_0229ef4c(UnkStruct_0229ef4c *o, int p1)
{
    void *heap;
    void *base;
    unsigned char *q;
    int i;
    int t;
    int local;
    int v;

    t = o->unk_E8;
    heap = data_021fbe94;
    base = func_02064b2c(data_ov124_0229f4a0[t / 5], heap, ~3, &local);
    q = (unsigned char *) base + (t % 5) * 0xc0;
    v = 0x15a;
    for (i = 0; i < 6; i++) {
        func_02002a88(q, 8, v, v, v + 5);
        q += 0x400;
        v += 0x20;
    }
    func_020e993c(heap, base);
    func_02002cd8(data_ov124_0229f610, heap, 8, o->unk_E8, p1);
    o->unk_E9 = p1;
    func_ov002_0220b36c(&o->unk_6C, data_ov124_0229f5d0, 0xe, 2);
    switch (func_0206fca4()) {
        case 0xb:
            func_ov002_0220b318(&o->unk_6C, 0x3b);
            break;
        case 0xf:
            func_ov002_0220b318(&o->unk_6C, 0xe6);
            break;
        case 0x10:
            func_ov002_0220b318(&o->unk_6C, 0xe7);
            break;
        case 0x18:
        case 0x19:
            func_ov002_0220b318(&o->unk_6C, 0xe9);
            break;
        case 0x1a:
        case 0x1b:
            func_ov002_0220b318(&o->unk_6C, 0xe8);
            break;
        case 0xc:
            func_ov002_0220b318(&o->unk_6C, 0x42);
            break;
        case 0xd:
            func_ov002_0220b318(&o->unk_6C, 0x44);
            break;
        case 0xe:
            func_ov002_0220b318(&o->unk_6C, 0x48);
            break;
        case 0x12:
            func_ov002_0220b318(&o->unk_6C, 0x4e);
            break;
        case 0x13:
            func_ov002_0220b318(&o->unk_6C, 0x4d);
            break;
        case 0x14:
            func_ov002_0220b318(&o->unk_6C, 0x4f);
            break;
        case 0x15:
            func_ov002_0220b318(&o->unk_6C, 0x45);
            break;
        case 0x16:
            func_ov002_0220b318(&o->unk_6C, 0x46);
            break;
        case 0x11:
            func_ov002_0220b318(&o->unk_6C, 0x4c);
            break;
        case 0x17:
            func_ov002_0220b318(&o->unk_6C, 0x41);
            break;
    }
}
