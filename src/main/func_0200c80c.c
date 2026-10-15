/* func_0200c80c @ 0x0200c80c, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

struct P1_sub {
    uint16_t s;     // offset 0x00
    char pad_02[2]; // 0x02
    uint32_t a;     // 0x04
    uint32_t b;     // 0x08
};

struct UnkStruct_0200c80c {
    char pad_00[0xc];  // 0x00
    struct P1_sub sub; // 0x0c
};

struct UnkStruct_0200c80c_2 {
    char pad_00[0x5c];   // 0x00
    uint32_t unk_5C;     // 0x5c
    char pad_60[0x2e];   // 0x60
    short unk_8E;        // 0x8e
    char pad_90[0x744];  // 0x90
    uint32_t unk_7D4;    // 0x7d4
    char pad_7D8[0x118]; // 0x7d8
    uint32_t unk_8F0;    // 0x8f0
};

extern void func_020109a0(struct UnkStruct_0200c80c_2 *p0, int r1, int r2, unsigned short r3);
extern void func_0200c8d8(void *addr, uint16_t s, uint32_t a, uint32_t b, int local);
extern void func_0200c8c0(void *addr, uint16_t s, uint8_t a, uint8_t b);
extern int func_0200f328(struct UnkStruct_0200c80c_2 *p0, int param);
extern int func_02091230(int arg0, void *arg1, int arg2, int arg3);

void func_0200c80c(struct UnkStruct_0200c80c_2 *p0, struct UnkStruct_0200c80c *p1, int previous)
{
    struct P1_sub *sub = &p1->sub;
    uint16_t s = p1->sub.s;
    uint32_t a = sub->a;
    uint32_t b = sub->b;

    if (b == 0x10) {
        func_020109a0(p0, 6, 3, 0);
    } else {
        func_020109a0(p0, 5, 3, 0);
    }

    func_0200c8d8((void *) &p0->unk_7D4, s, a, b, p0->unk_8E);
    func_0200c8c0((void *) &p0->unk_8F0, s, (uint8_t) a, (uint8_t) b);

    if (a == 2 && s == 0x13c3) {
        func_0200f328(p0, 0x77);
    } else {
        func_0200f328(p0, 0x76);
    }

    func_02091230(0x61, (void *) &p0->unk_5C, 0, 0);
}
