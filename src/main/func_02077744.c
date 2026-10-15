/* func_02077744 @ 0x02077744, 0xa6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Entry {
    unsigned char pad_00[0x20];
    unsigned int unk_20;
    unsigned short unk_24;
};

extern void func_0209bd80(void *);
extern void func_0209bd7c(void *);
extern struct Entry *func_0207b9d0(int);
extern void func_020794d4(struct Entry *, unsigned char);
extern int func_020794d0(struct Entry *);
extern int func_0209bc40(void *);
extern int func_0209bb70(void *);
extern void func_0209bd30(int, int, int, int);
extern void MI_CpuCopy8(void *, const void *, unsigned int);

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
        e = func_0207b9d0(i);
        rec.b = 3;
        MI_CpuCopy8(out, &rec.b, 1);
        func_020794d4(e, rec.b);
        MI_CpuCopy8(out + 1, buf, 12);

        a = func_020794d0(e);
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
