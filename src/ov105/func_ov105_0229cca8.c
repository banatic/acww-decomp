/* func_ov105_0229cca8 @ 0x0229cca8, 0x4c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *ptr, int val);
extern void func_ov002_0220a374(void *ptr, int val);
extern void func_ov002_02208098(void *ptr, int val);

struct UnkStruct_0229cca8 {
    char pad_00[0x8d];
    unsigned char byte_at_8d;
    char pad_8E[0x22e];
    unsigned char byte_at_2bc;
    unsigned char byte_at_2bd;
    char pad_2BE[0x20fe];
    unsigned int unk_23BC;
    char pad_23C0[0xe4];
    unsigned int unk_24A4;
};

void func_ov105_0229cca8(struct UnkStruct_0229cca8 *p, unsigned char c)
{
    func_ov002_02207d24(&p->unk_23BC, 1);
    p->byte_at_2bd = p->byte_at_8d;
    p->byte_at_2bc = c;
    func_ov002_0220a374(&p->unk_24A4, 6);
    func_ov002_02208098(p, 0x13);
}
