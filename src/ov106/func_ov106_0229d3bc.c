/* func_ov106_0229d3bc @ 0x0229d3bc, 0x2c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229d3bc {
    unsigned char pad_00[0xbe];
    unsigned char flag;
    unsigned char pad_BF[0x3ef5];
    unsigned char data[4];
};

extern void func_0200467c(unsigned int);
extern void *func_ov002_0220a720(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov106_0229d3bc(struct UnkStruct_0229d3bc *p)
{
    func_0200467c(0x28);
    func_ov002_0220a720(p->data, 4);
    func_ov002_02208098((void *) (p), 0x1f);
    p->flag = 1;
}
