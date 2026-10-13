/* func_020f5054 @ 0x020f5054, 0x90 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned char data_021fd1bc[];
extern unsigned int data_021fd234;
extern void func_020f51c4(void);
extern void func_020f4eec(unsigned int a, void *b, const unsigned int *c);

struct Dst {
    char pad_00[0xc];
    unsigned int f0;
    unsigned int f1;
    unsigned int f2;
    short unk_18;
    unsigned char unk_1A;
    unsigned char unk_1B;
};

struct Src {
    unsigned int f0;
    unsigned int f1;
    unsigned int f2;
};

void func_020f5054(struct Dst *dst, int type, struct Src *src)
{
    if (data_021fd1bc[0x4d]) {
        return;
    }
    dst->unk_18 = type;
    dst->f0 = src->f0;
    dst->f1 = src->f1;
    dst->f2 = src->f2;
    dst->unk_1A = 0;
    dst->unk_1B = 1;
    if (type == 0x4ef) {
        func_020f51c4();
    } else {
        func_020f4eec(data_021fd234, dst, &data_021fd234);
    }
}
