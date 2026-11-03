/* music_list_scene: 6 functions, module ov144
 * mwccarm 1.2/base -O4,s
 * func_ov144_0229a9d4 @ 0x0229a9d4, 0x32 bytes, Thumb
 * func_ov144_0229a9b0 @ 0x0229a9b0, 0x24 bytes, Thumb
 * func_ov144_0229a948 @ 0x0229a948, 0x68 bytes, Thumb
 * func_ov144_0229a894 @ 0x0229a894, 0xb4 bytes, Thumb
 * func_ov144_0229a868 @ 0x0229a868, 0x2c bytes, Thumb
 * func_ov144_0229a83c @ 0x0229a83c, 0x2c bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
    int unk_A4;
    unsigned char pad_A8[0xb8 - 0xa8];
    short unk_B8;
    short unk_BA;
    short unk_BC;
    unsigned char pad_BE[0xc0 - 0xbe];
    unsigned char unk_C0;
    unsigned char pad_C1[0x86c - 0xc1];
    unsigned short table[1];
} UnkStruct_0229a894;

struct S_f858 {
    unsigned char pad_00[0xc0];
    volatile unsigned char unk_C0;
};

extern int func_0208e484(void *p);
extern int func_ov144_02299ac4(void *p, int c);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void func_ov144_0229a0a4(void *p);
extern void func_ov144_0229a0e0(void *);
extern int func_0208e4bc(void *);
extern void func_ov144_0229a17c(void *);
extern int func_ov002_0220a700(void *);
extern int func_ov002_0220a6e0(void *);
extern int func_ov002_0220a768(void *, int);
extern int func_ov002_0220a72c(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern unsigned char *func_ov002_022080a0(void *, unsigned char value);
extern void func_02060984(unsigned int item);
extern int func_ov144_02299b48(UnkStruct_0229a894 *self, int);
extern void func_ov144_0229a328(UnkStruct_0229a894 *self);
extern void func_ov144_02299e6c(UnkStruct_0229a894 *self, int);
extern void func_ov144_0229a378(UnkStruct_0229a894 *self);
extern int func_ov144_0229a7c8(UnkStruct_0229a894 *self);
extern int func_ov002_0220b8ac(char *, int);
extern void func_0208e5cc(char *);

void func_ov144_0229a9d4(void *p)
{
    if (func_0208e484((char *) p + 0xc4)) {
        if (func_ov144_02299ac4(p, *(unsigned char *) ((char *) p + 0xc1)) == 0) {
            func_ov002_02208098(p, 3);
            func_ov144_0229a0a4(p);
        }
    }
}

void func_ov144_0229a9b0(void *arg0)
{
    if (func_0208e484((char *) arg0 + 0xc4)) {
        func_ov144_0229a0e0(arg0);
        func_ov002_02208098(arg0, *(unsigned char *) ((char *) arg0 + 0xbe));
    }
}

void func_ov144_0229a948(void *self)
{
    if (func_ov002_0220a700((char *) self + 0x170)) {
        if (func_0208e4bc((char *) self + 0xc4)) {
            int r4 = func_ov002_0220a6e0((char *) self + 0x170);
            int r6 = func_ov002_0220a768((char *) self + 0x170, -1);
            int r2 = func_ov002_0220a72c((char *) self + 0x170, -1);
            func_ov002_0220a0b4((char *) self + 0xc4, r4 + r6, r4 + r2);
        }
    } else {
        func_ov144_0229a17c(self);
        func_ov002_022080a0(self, 1);
    }
}

void func_ov144_0229a894(UnkStruct_0229a894 *self)
{
    if (self->unk_C0 != 0) {
        self->unk_C0--;
    } else {
        func_02060984(self->table[self->unk_BA]);
        if (self->unk_BA < self->unk_BC) {
            self->unk_BC -= 1;
        }
        func_ov144_02299b48(self, -1);
        func_ov144_0229a328(self);
        self->unk_A4 = (self->unk_B8 - 8) << 4;
        if (self->unk_A4 < 0) {
            self->unk_A4 = 0;
        }
        if (self->unk_9C > self->unk_A4) {
            self->unk_9C = self->unk_A4;
        }
        func_ov144_02299e6c(self, self->unk_9C);
        self->unk_A0 = self->unk_9C;
        func_ov144_0229a378(self);
        func_ov144_0229a7c8(self);
    }
}

void func_ov144_0229a868(struct S_f858 *s)
{
    if (s->unk_C0 != 0) {
        s->unk_C0 = s->unk_C0 - 1;
    } else {
        func_ov144_0229a17c(s);
        func_ov002_022080a0(s, 1);
    }
}

void func_ov144_0229a83c(char *arg)
{
    char *p;

    p = arg;
    if (func_ov002_0220b8ac(p + 0x750, 1) != 0) {
        func_ov144_0229a7c8((UnkStruct_0229a894 *) p);
        p += 0xc4;
        func_0208e5cc(p);
    }
}
