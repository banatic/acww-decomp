/* insect_catalog: 4 functions, module ov116
 * mwccarm 1.2/base -O4,s
 * func_ov116_0229ddf8 @ 0x0229ddf8, 0x18 bytes, Thumb
 * func_ov116_0229ddd0 @ 0x0229ddd0, 0x28 bytes, Thumb
 * func_ov116_0229ddb8 @ 0x0229ddb8, 0x18 bytes, Thumb
 * func_ov116_0229dda8 @ 0x0229dda8, 0x10 bytes, Thumb
 */

struct UnkStruct_0229ddd0 {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0x94 - 0x8e];
    unsigned char unk_94;
    char pad_95[0x142c - 0x95];
    unsigned char unk_142C;
};

typedef struct {
    char pad_00[0x1428];
    unsigned short unk_1428;
} StructAtOffset1428;

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov002_0220a164(void *p);

void func_ov116_0229ddf8(void *self)
{
    func_ov002_0220a1dc((char *) self + 0x94);
    func_ov002_02208098(self, 4);
}

unsigned char *func_ov116_0229ddd0(struct UnkStruct_0229ddd0 *obj)
{
    func_ov002_0220a164(&obj->unk_94);
    obj->unk_142C = obj->unk_8D;
    return func_ov002_02208098(obj, 5);
}

int func_ov116_0229ddb8(StructAtOffset1428 *obj, unsigned short mask)
{
    if ((obj->unk_1428 & mask) == 0) {
        return 0;
    } else {
        return 1;
    }
}

void func_ov116_0229dda8(unsigned short *p, unsigned short mask)
{
    unsigned short *q = (unsigned short *) ((char *) p + 0x1428);
    *q = (unsigned short) (*q | mask);
}
