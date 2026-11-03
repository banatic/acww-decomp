/* my_designs_use_4: 2 functions, module ov121
 * mwccarm 1.2/base -O4,s
 * func_ov121_0229b0bc @ 0x0229b0bc, 0x26 bytes, Thumb
 * func_ov121_0229b09c @ 0x0229b09c, 0x1e bytes, Thumb
 */

struct UnkStruct_0229b09c {
    char pad_00[0xb7];
    unsigned char unk_B7;
};

extern int func_ov121_02299ad8(void *p, unsigned char b, unsigned short h);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern int func_ov121_02299aac(void *p, unsigned char b);
extern unsigned char *func_ov121_0229afb8(void *p);

int func_ov121_0229b0bc(void *p)
{
    int r = func_ov121_02299ad8(p, *(unsigned char *) ((char *) p + 0xb7), *(unsigned short *) ((char *) p + 0xa0));
    if (r != 0) {
        r = (int) func_ov002_02208098(p, 0x12);
    }
    return r;
}

void func_ov121_0229b09c(struct UnkStruct_0229b09c *p)
{
    if (func_ov121_02299aac(p, p->unk_B7) != 0) {
        func_ov121_0229afb8(p);
    }
}
