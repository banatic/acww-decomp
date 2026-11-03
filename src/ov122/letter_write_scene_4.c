/* letter_write_scene_4: 6 functions, module ov122
 * mwccarm 1.2/base -O4,s
 * func_ov122_0229f444 @ 0x0229f444, 0x10 bytes, Thumb
 * func_ov122_0229f3c8 @ 0x0229f3c8, 0x7c bytes, Thumb
 * func_ov122_0229f394 @ 0x0229f394, 0x34 bytes, Thumb
 * func_ov122_0229f388 @ 0x0229f388, 0xc bytes, Thumb
 * func_ov122_0229f348 @ 0x0229f348, 0x40 bytes, Thumb
 * func_ov122_0229f2f4 @ 0x0229f2f4, 0x54 bytes, Thumb
 */

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    char pad_A4[0xb3 - 0xa0 - 4];
    unsigned char unk_B3;
} UnkStruct_0229f394;

extern int func_ov122_0229efe8(int, int);
extern void func_ov122_0229efc8(void *p, unsigned int v);
extern void func_ov122_0229f454(UnkStruct_0229f394 *p, int value);
extern void func_0200467c(int);
extern void *func_ov002_0220a720(void *addr, unsigned char byte);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern const unsigned char data_ov122_022a2584[];
extern const unsigned short data_ov122_022a258c[];
extern void func_ov095_02299aec(unsigned char *);
extern int func_ov095_02299b7c(unsigned char *);
extern int func_ov095_02299b38(unsigned char *);
extern void func_ov002_0220a0b4(unsigned char *, int, int);
extern void func_ov002_0220a374(unsigned char *, int);
extern void func_ov122_0229f150(unsigned char *);

int func_ov122_0229f444(int p0)
{
    return func_ov122_0229efe8(p0, 2048);
}

void func_ov122_0229f3c8(unsigned char *p)
{
    if (p[0xb2] == p[0xb3]) {
        func_ov122_0229efc8(p, 0x800);
        return;
    }
    if (p[0xb2] < p[0xb3]) {
        p[0xb2] += 8;
        if (p[0xb2] > p[0xb3]) {
            p[0xb2] = p[0xb3];
        }
    } else {
        if (p[0xb2] < 8) {
            p[0xb2] = p[0xb3];
        } else {
            p[0xb2] -= 8;
            if (p[0xb2] < p[0xb3]) {
                p[0xb2] = p[0xb3];
            }
        }
    }
}

void func_ov122_0229f394(UnkStruct_0229f394 *p)
{
    unsigned char b = p->unk_B3;
    int v = p->unk_A0;
    int diff = v - b;
    if (diff < 24) {
        func_ov122_0229f454(p, b - (24 - diff));
    } else if (diff > 48) {
        func_ov122_0229f454(p, b + (diff - 48));
    }
}

void func_ov122_0229f388(void *receiver)
{
    func_0200467c(0x34);
}

void func_ov122_0229f348(void *this_, int index)
{
    func_ov002_0220a720(((char *) this_ + 0x4698), data_ov122_022a2584[index]);
    ((unsigned char *) this_)[0xb8] = (unsigned char) index;
    func_ov002_02208098((void *) (this_), 25);
    func_0200467c((unsigned short) data_ov122_022a258c[index]);
}

void func_ov122_0229f2f4(unsigned char *self)
{
    int x, y;

    func_ov122_0229efc8((void *) self, 0x100);
    func_ov095_02299aec(self + 0xc0);
    x = func_ov095_02299b7c(self + 0xc0);
    y = func_ov095_02299b38(self + 0xc0);
    func_ov002_0220a0b4(self + 0x4058, x, y);
    func_ov002_0220a374(self + 0x4058, 1);
    func_ov122_0229f150(self);
}
