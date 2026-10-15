/* func_ov108_0229c72c @ 0x0229c72c, 0x68 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c72c {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0x222];
    unsigned char unk_2B0;
    unsigned char pad_2B1[2];
    unsigned char unk_2B3;
    unsigned char pad_2B4[0x21e4];
    unsigned char sub_2498[1];
};

extern void func_ov002_0220a314(void *ptr);
extern void func_ov002_0220a2b4(void *ptr);
extern void func_ov002_0220a05c(void *ptr, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov108_0229c7c8(void *ptr);
extern int func_ov108_0229c7b8(void *ptr);

void func_ov108_0229c72c(struct UnkStruct_0229c72c *p)
{
    if (p->unk_2B0 == 0x15) {
        func_ov002_0220a314(&p->sub_2498);
    } else {
        func_ov002_0220a2b4(&p->sub_2498);
    }
    {
        int a = func_ov108_0229c7c8(p);
        int b = func_ov108_0229c7b8(p);
        func_ov002_0220a05c(&p->sub_2498, a, b, 3, 1);
    }
    p->unk_2B3 = p->unk_8D;
    func_ov002_02208098((void *) (p), 0xa);
}
