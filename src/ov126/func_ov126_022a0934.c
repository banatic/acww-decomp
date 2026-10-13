/* func_ov126_022a0934 @ 0x022a0934, 0x44 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022a0934 {
    unsigned char pad_00[0x98];
    unsigned int unk_98;
    unsigned int unk_9C;
    unsigned char pad_A0[0xab - 0xa0];
    unsigned char unk_AB;
};

extern void func_ov126_0229f7b8(struct UnkStruct_022a0934 *, int);
extern void func_ov126_022a0924(struct UnkStruct_022a0934 *, int);
extern void func_ov126_022a0728(struct UnkStruct_022a0934 *);
extern void func_ov095_0229cd30(void *);
extern void func_ov126_022a0978(struct UnkStruct_022a0934 *);

void func_ov126_022a0934(struct UnkStruct_022a0934 *p)
{
    func_ov126_0229f7b8(p, 2);
    p->unk_98 = p->unk_AB;
    p->unk_9C = 0x28;
    func_ov126_022a0924(p, 0);
    func_ov126_022a0728(p);
    func_ov095_0229cd30((char *) p + 0x19c);
    func_ov126_022a0978(p);
}
