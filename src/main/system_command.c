/* system_command: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02077864 @ 0x02077864, 0x2 bytes, Thumb
 * func_020777f0 @ 0x020777f0, 0x74 bytes, Thumb
 * func_020777ec @ 0x020777ec, 0x2 bytes, Thumb
 * func_02077744 @ 0x02077744, 0xa6 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x20];
    unsigned int unk_20;
    unsigned short unk_24;
} PStruct;

typedef struct {
    unsigned char a;
    unsigned short b;
    unsigned int c;
} UnkStruct_020777f0;

struct Entry {
    unsigned char pad_00[0x20];
    unsigned int unk_20;
    unsigned short unk_24;
};

extern void *data_020ccf94;
extern void *func_0207b9d0(int);
extern unsigned char func_020794d8(void *);
extern void *func_020794d0(void *p);
extern void func_020732f0(void *, const void *, unsigned int);
extern void func_0209bd80(void *);
extern void func_0209bd7c(void *);
extern void func_020794d4(struct Entry *, unsigned char);
extern int func_0209bc40(void *);
extern int func_0209bb70(void *);
extern void func_0209bd30(int, int, int, int);
extern void MI_CpuCopy8(void *, const void *, unsigned int);

void func_02077864(void *source) {}

void func_020777f0(void *source)
{
    PStruct *p;
    int i;
    void *base;
    UnkStruct_020777f0 local;
    local.a = 3;
    i = 0;
    base = data_020ccf94;
    for (; i < 8; i++) {
        p = (PStruct *) func_0207b9d0(i);
        if (p != 0) {
            local.a = func_020794d8(p);
        } else {
            local.a = 3;
        }
        func_020732f0(base, &local.a, 1);
        func_020732f0(base, func_020794d0(p), 12);
        local.c = p->unk_20;
        func_020732f0(base, &local.c, 4);
        local.b = p->unk_24;
        func_020732f0(base, &local.b, 2);
    }
}

void func_020777ec(void *payload, unsigned short length) {}

void func_02077744(unsigned char *out, unsigned short length)
{
    int a, b;
    unsigned int z1, z2, z3;
    struct {
        unsigned char b;
        unsigned short h;
    } rec;
    unsigned int data;
    char buf[12];
    int i;
    struct Entry *e;

    rec.b = 3;
    func_0209bd80(buf);
    z1 = 0;
    z2 = 0;
    z3 = 0;

    for (i = 0; i < 8; i++) {
        e = (struct Entry *) func_0207b9d0(i);
        rec.b = 3;
        MI_CpuCopy8(out, &rec.b, 1);
        func_020794d4(e, rec.b);
        MI_CpuCopy8(out + 1, buf, 12);

        a = (int) func_020794d0((void *) e);
        b = func_0209bc40(buf);
        func_0209bd30(a, b, func_0209bb70(buf), z1);

        data = z2;
        MI_CpuCopy8(out + 13, &data, 4);
        e->unk_20 = data;

        rec.h = (unsigned short) z3;
        MI_CpuCopy8(out + 17, &rec.h, 2);
        e->unk_24 = rec.h;

        out += 19;
    }

    func_0209bd7c(buf);
}
