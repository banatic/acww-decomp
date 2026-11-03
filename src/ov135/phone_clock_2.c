/* phone_clock_2: 2 functions, module ov135
 * mwccarm 1.2/base -O4,s
 * func_ov135_0229c6e8 @ 0x0229c6e8, 0x50 bytes, Thumb
 * func_ov135_0229c688 @ 0x0229c688, 0x5e bytes, Thumb
 */

typedef struct UnkStruct_0229c6e8 {
    char pad_00[0x95];
    unsigned char unk_95;
    char pad_96[2];
    char unk_98;
} UnkStruct_0229c6e8;

extern int func_ov135_0229c574(UnkStruct_0229c6e8 *, int);
extern int func_ov135_0229c7a8(UnkStruct_0229c6e8 *);
extern int func_ov135_0229c754(UnkStruct_0229c6e8 *);
extern void func_ov002_0220a2b4(void *);
extern void func_ov002_0220a314(void *);
extern void func_ov135_0229c554(unsigned char *self, int a);
extern void func_ov002_0220a05c(unsigned char *ptr, int p1, int p2, int a, int b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov135_0229c688(unsigned char *self, int p1, int p2);

void func_ov135_0229c6e8(UnkStruct_0229c6e8 *self)
{
    int a;
    int b;

    if (func_ov135_0229c574(self, 2) != 0 || (self->unk_95 != 5 && self->unk_95 != 6)) {
        func_ov002_0220a2b4(&self->unk_98);
    } else {
        func_ov002_0220a314(&self->unk_98);
    }

    a = func_ov135_0229c7a8(self);
    b = func_ov135_0229c754(self);
    func_ov135_0229c688((unsigned char *) self, a, b);
}

void func_ov135_0229c688(unsigned char *self, int p1, int p2)
{
    if (func_ov135_0229c574((UnkStruct_0229c6e8 *) self, 4)) {
        func_ov002_0220a05c(self + 0x98, p1, p2, 2, 1);
    } else {
        func_ov002_0220a05c(self + 0x98, p1, p2, 3, 1);
    }
    self[0x94] = self[0x8d];
    func_ov002_02208098((void *) (self), 0xa);
    func_ov135_0229c554(self, 4);
}
