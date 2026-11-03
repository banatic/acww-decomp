/* tune_editor_3: 2 functions, module ov143
 * mwccarm 1.2/base -O4,s
 * func_ov143_02299fd0 @ 0x02299fd0, 0x44 bytes, Thumb
 * func_ov143_02299fa0 @ 0x02299fa0, 0x30 bytes, Thumb
 */

struct UnkStruct_02299fd0 {
    char pad_00[0xa4];
    unsigned char unk_A4;
    char pad_A5[7];
    char unk_AC;
};

typedef struct {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0x10];
    unsigned char unk_9E;
    char pad_9F[0xd];
    char unk_AC;
} UnkStruct_02299fa0;

extern void func_ov002_0220a314(void *);
extern void func_ov002_0220a2b4(void *);
extern int func_ov143_0229a0b0(void *);
extern int func_ov143_0229a030(void *);
extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

void func_ov143_02299fa0(UnkStruct_02299fa0 *self, int a, int b);

void func_ov143_02299fd0(struct UnkStruct_02299fd0 *p)
{
    int x, y;
    if (p->unk_A4 == 0x12) {
        goto then;
    }
    if (p->unk_A4 != 0x13) {
        goto els;
    }
then:
    func_ov002_0220a314(&p->unk_AC);
    goto after;
els:
    func_ov002_0220a2b4(&p->unk_AC);
after:
    x = func_ov143_0229a0b0(p);
    y = func_ov143_0229a030(p);
    func_ov143_02299fa0((UnkStruct_02299fa0 *) p, x, y);
}

void func_ov143_02299fa0(UnkStruct_02299fa0 *self, int a, int b)
{
    func_ov002_0220a05c(&self->unk_AC, a, b, 3, 1);
    self->unk_9E = self->unk_8D;
    func_ov002_02208098(self, 4);
}
