/* func_ov143_02299f48 @ 0x02299f48, 0x24 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a164(void *p);
extern void func_ov002_02208098(void *p, int n);

typedef struct {
    char pad_00[0x8D];
    unsigned char unk_8D;
    char pad_8E[0x10];
    unsigned char unk_9E;
    char pad_9F[0xD];
    char unk_AC;
} UnkStruct_02299f48;

void func_ov143_02299f48(UnkStruct_02299f48 *p)
{
    func_ov002_0220a164(&p->unk_AC);
    p->unk_9E = p->unk_8D;
    func_ov002_02208098(p, 6);
}
