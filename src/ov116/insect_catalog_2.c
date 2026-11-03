/* insect_catalog_2: 2 functions, module ov116
 * mwccarm 1.2/base -O4,s
 * func_ov116_0229de60 @ 0x0229de60, 0x52 bytes, Thumb
 * func_ov116_0229de2c @ 0x0229de2c, 0x34 bytes, Thumb
 */

typedef struct UnkStruct_0229de60 UnkStruct_0229de60;

struct UnkStruct_0229de60 {
    unsigned char pad_00[0x94];
    char unk_94;
    unsigned char pad_95[0x63];
    char unk_F8;
};

struct UnkStruct_0229de2c {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0x06];
    char unk_94;
    char pad_95[0x1397];
    unsigned char unk_142C;
};

extern int func_ov114_0229c60c(const void *);
extern int func_ov114_0229c5f4(const void *);
extern void func_ov002_0220a254(const void *);
extern void func_ov002_0220a2b4(const void *);
extern int func_ov116_0229dedc(const UnkStruct_0229de60 *);
extern int func_ov116_0229ded0(const UnkStruct_0229de60 *);
extern void func_ov002_0220a05c(char *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(struct UnkStruct_0229de2c *p, unsigned char value);

void func_ov116_0229de2c(struct UnkStruct_0229de2c *self, int a, int b);

void func_ov116_0229de60(UnkStruct_0229de60 *obj)
{
    int t1, t2;

    if (func_ov114_0229c60c(&obj->unk_F8) != -1 || func_ov114_0229c5f4(&obj->unk_F8) != 0) {
        func_ov002_0220a254(&obj->unk_94);
    } else {
        func_ov002_0220a2b4(&obj->unk_94);
    }

    t1 = func_ov116_0229dedc(obj);
    t2 = func_ov116_0229ded0(obj);
    func_ov116_0229de2c((struct UnkStruct_0229de2c *) obj, t1, t2);
}

void func_ov116_0229de2c(struct UnkStruct_0229de2c *self, int a, int b)
{
    func_ov002_0220a05c(&self->unk_94, a, b, 3, 1);
    self->unk_142C = self->unk_8D;
    func_ov002_02208098(self, 3);
}
