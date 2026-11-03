/* bbs_write_text: 8 functions, module ov112
 * mwccarm 1.2/base -O4,s
 * func_ov112_0229f1f4 @ 0x0229f1f4, 0x5c bytes, Thumb
 * func_ov112_0229f11c @ 0x0229f11c, 0xd8 bytes, Thumb
 * func_ov112_0229f0ec @ 0x0229f0ec, 0x30 bytes, Thumb
 * func_ov112_0229f0b4 @ 0x0229f0b4, 0x38 bytes, Thumb
 * func_ov112_0229f078 @ 0x0229f078, 0x3c bytes, Thumb
 * func_ov112_0229f058 @ 0x0229f058, 0x20 bytes, Thumb
 * func_ov112_0229efe8 @ 0x0229efe8, 0x70 bytes, Thumb
 * func_ov112_0229efbc @ 0x0229efbc, 0x2c bytes, Thumb
 */

typedef struct {
    char pad_00[0xb4];
    short unk_B4;
} UnkStruct_0229efbc;

extern void func_020a8874(void *dst, void *src, int size);
extern int func_020a8a70(void *dst, void *src, int a, int b);
extern int func_020b4424(void *p);
extern int func_020a87e0(void *dst, void *src);
extern int func_0205182c(void *dst, void *src, int size);
extern void func_0209df64(void *);
extern void func_020708e4(unsigned short *, const unsigned short *, int);
extern void func_020a8c1c(void *);
extern void func_02070a98(void *receiver, int p2, int p3, int p4, unsigned char p5, unsigned char p6, int flag);
extern void func_02070a04(void *p, int a, int b);
extern void func_02001a7c(void);
extern void func_02001a1c(int);
extern void func_ov002_0220a6b8(void *);
extern void func_02001d60(int, int);
extern void func_02001b7c(int);
extern void func_02001c58(int, int, int, int);
extern void func_02001a5c(void);
extern void func_02001b6c(int);
extern void func_ov002_0220a690(void *);
extern void *data_020ccf94;
extern void *data_021c9b28;
extern int func_02073d90(void *);
extern void *func_020e9958(void *heap, unsigned int size);
extern void func_020e993c(void *heap, void *p);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, int);
extern void func_02073770(void *, int, int);
extern short func_02073d80(void *);
extern int func_02074fec(int);

void func_ov112_0229f0b4(void *base, int idx, int p2, int p3, int p4);

void func_ov112_0229f1f4(void *self)
{
    char *base = (char *) self;
    char *p = base + 0xc4;
    func_020a8874(base + 0x4580, p, 0x60);
    func_020a8a70(base + 0x44ac, base + 0x4580, 0, 0);
    if (func_020b4424(base + 0x44ac) != 0) {
        func_020a87e0(base + 0x4580, base + 0x44ac);
        func_0205182c(base + 0x4580, p, 0x60);
    }
}

void func_ov112_0229f11c(void *self)
{
    struct {
        unsigned char pad[3];
        unsigned short arr[5];
    } data;
    unsigned char v0, v1, v2;

    func_0209df64(&data);
    data.arr[0] = 0xff12;
    data.arr[1] = 0xff10;
    v2 = data.pad[2];
    data.arr[2] = v2 / 10 + 0xff10;
    data.arr[3] = v2 % 10 + 0xff10;
    data.arr[4] = 0;
    func_020708e4((unsigned short *) ((unsigned char *) self + 0x3fac), data.arr, 5);
    func_ov112_0229f0b4(self, 0, 0x111, 4, 1);

    v1 = data.pad[1];
    data.arr[0] = v1 / 10 + 0xff10;
    data.arr[1] = v1 % 10 + 0xff10;
    v0 = data.pad[0];
    data.arr[2] = v0 / 10 + 0xff10;
    data.arr[3] = v0 % 10 + 0xff10;
    func_020708e4((unsigned short *) ((unsigned char *) self + 0x4018), data.arr, 5);
    func_ov112_0229f0b4(self, 1, 0x116, 4, 1);
}

void func_ov112_0229f0ec(void *self)
{
    func_020a8c1c((char *) self + 0x4084);
    func_ov112_0229f0b4(self, 2, 0x11A, 5, 0);
}

void func_ov112_0229f0b4(void *base, int idx, int p2, int p3, int p4)
{
    void *p = (char *) base + 0x3fac + idx * 0x6c;
    func_02070a98(p, 4, p2, p3, 15, 10, p4);
    func_02070a04(p, 0, 0);
}

void func_ov112_0229f078(void *param)
{
    func_02001a7c();
    func_02001a1c(~5);
    func_ov002_0220a6b8((char *) param + 0x427c);
    func_02001d60(0x1f, 0);
    func_02001b7c(2);
    func_02001c58(0x2c, 0x20, 0xd4, 0x80);
}

void func_ov112_0229f058(void *arg)
{
    func_02001a5c();
    func_ov002_0220a690((char *) arg + 0x427c);
    func_02001b6c(2);
}

void func_ov112_0229efe8(void *obj)
{
    void *heap;
    unsigned char *buf;
    void *ptr;

    if (func_02073d90(data_020ccf94) != 0) {
        heap = data_021c9b28;
        buf = (unsigned char *) func_020e9958(heap, 0xc1);
        buf[0] = 0;
        MI_CpuCopy8((char *) obj + 0xc4, buf + 1, 0xc0);
        ptr = data_020ccf94;
        func_02073820(ptr);
        func_020737f0(ptr, buf, 0xc1);
        func_02073770(ptr, 0x16, 4);
        *(short *) ((char *) obj + 0xb4) = func_02073d80(ptr);
        func_020e993c(heap, buf);
    }
}

int func_ov112_0229efbc(UnkStruct_0229efbc *p)
{
    if (func_02073d90(data_020ccf94) != 0 && func_02074fec(p->unk_B4) == 0) {
        return 0;
    } else {
        return 1;
    }
}
