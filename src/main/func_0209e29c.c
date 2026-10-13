/* func_0209e29c @ 0x0209e29c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0209e29c {
    unsigned char pad_00[3];
    unsigned char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
};

extern int func_0209de24(unsigned char, unsigned char);
extern void func_0209e2d0(struct UnkStruct_0209e29c *, int);

void func_0209e29c(struct UnkStruct_0209e29c *s, int arg)
{
    int limit = func_0209de24(s->unk_05, s->unk_04);
    int cur = s->unk_03 + arg;
    while (cur > limit) {
        cur -= limit;
        func_0209e2d0(s, 1);
        limit = func_0209de24(s->unk_05, s->unk_04);
    }
    s->unk_03 = (unsigned char) cur;
}
