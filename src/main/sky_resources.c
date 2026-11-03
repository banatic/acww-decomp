/* sky_resources: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bec70 @ 0x020bec70, 0x34 bytes, Thumb
 * func_020bec60 @ 0x020bec60, 0x10 bytes, Thumb
 * func_020bec54 @ 0x020bec54, 0xc bytes, Thumb
 * func_020bec40 @ 0x020bec40, 0x12 bytes, Thumb
 * func_020bec14 @ 0x020bec14, 0x2c bytes, Thumb
 */

struct UnkStruct_020bec40 {
    unsigned short pad_00[4];
    unsigned short unk_08;
};

extern struct Entry {
    signed char pad_00[12];
    signed char unk_0C;
    signed char unk_0D;
    signed char pad_0E[2];
} data_020d2bac[];
extern unsigned char data_020d2324[];
extern void func_020becbc(unsigned short *obj, int val, int mask, unsigned short *dst);

int func_020bec70(signed char *arg0, int arg1)
{
    struct Entry *entry = &data_020d2bac[arg1];
    signed char d = entry->unk_0D;
    signed char c = entry->unk_0C;
    int result = 1;
    if (d >= 0 && c >= 0) {
        if (c != (arg0 + (d - 12))[4]) {
            result = 0;
        }
    }
    return result;
}

void func_020bec60(char *p, int off, char val)
{
    if (off >= 0 && val >= 0) {
        p += off - 12;
        p[4] = val;
    }
}

void func_020bec54(unsigned short *r0, int r1)
{
    unsigned short r3;
    int r2;

    r3 = r0[4]; // offset 8 = 4 * sizeof(unsigned short)
    r2 = 1;
    r2 = r2 << r1;
    r3 = r3 & ~r2;
    r0[4] = r3;
}

int func_020bec40(struct UnkStruct_020bec40 *p, int bit)
{
    return (p->unk_08 & (1 << bit)) ? 1 : 0;
}

void func_020bec14(unsigned short *obj, int index, const unsigned short *src)
{
    unsigned short *p;
    obj[4] |= 1 << index;
    p = obj + index;
    p[5] = *src;
    func_020becbc(obj, (data_020d2324[index] >> 4) & 0xf, 0xf, p);
}
