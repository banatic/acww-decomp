/* func_ov094_02299d8c @ 0x02299d8c, 0x40 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02299d8c UnkStruct_02299d8c;
struct UnkStruct_02299d8c {
    unsigned char pad_00[0xe];
    unsigned char unk_0E;
    unsigned char pad_0F[0x70 - 0xf];
};

extern int func_ov094_022999b0(UnkStruct_02299d8c *p, int n);
extern void func_ov094_022999a0(UnkStruct_02299d8c *p, int n);
extern int func_020b9c10(char *a, char *b, int c, int d, int e, int f);

void func_ov094_02299d8c(UnkStruct_02299d8c *p)
{
    if (func_ov094_022999b0(p, 4) != 0) {
        if (func_020b9c10((char *) p + 0x70, (char *) p + 0x9b8, p->unk_0E, 0x35, 0x35, 0x98) != 0) {
            func_ov094_022999a0(p, 4);
        }
    }
}
