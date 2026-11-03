/* letter_write_scene: 9 functions, module ov122
 * mwccarm 1.2/base -O4,s
 * func_ov122_0229f104 @ 0x0229f104, 0x4c bytes, Thumb
 * func_ov122_0229f0dc @ 0x0229f0dc, 0x28 bytes, Thumb
 * func_ov122_0229f0a8 @ 0x0229f0a8, 0x34 bytes, Thumb
 * func_ov122_0229f088 @ 0x0229f088, 0x1e bytes, Thumb
 * func_ov122_0229f034 @ 0x0229f034, 0x54 bytes, Thumb
 * func_ov122_0229effc @ 0x0229effc, 0x36 bytes, Thumb
 * func_ov122_0229efe8 @ 0x0229efe8, 0x12 bytes, Thumb
 * func_ov122_0229efd8 @ 0x0229efd8, 0xe bytes, Thumb
 * func_ov122_0229efc8 @ 0x0229efc8, 0xe bytes, Thumb
 */

typedef struct {
    char pad_00[0xbc];
    unsigned char *data;
} UnkStruct_0229effc;

struct UnkStruct_0229efe8 {
    unsigned char pad_00[0xa8];
    unsigned short unk_A8;
};

typedef struct {
    unsigned char pad_00[0xa8];
    unsigned short unk_A8;
} UnkStruct_0229efc8;

extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char c);
extern int func_ov002_0220a08c(void *p, int a, int b, int c);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_02209740(char *a, unsigned char b, int c);
extern void func_0200467c(int);
extern void func_ov002_022096d8(void *, int);
extern void func_ov122_0229f2d0(void *);
extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098ddc(int);
extern void func_02065db8(int, int);
extern void func_020a8874(void *object, const void *source, int length);
extern int func_020a8a70(char *p1, char *p2, int a, int b);
extern int func_020b4424(char *p);
extern int func_020a87e0(char *p1, char *p2);
extern int func_0205182c(char *p1, int a, int b);

void func_ov122_0229f104(unsigned char *arg)
{
    int a = func_ov002_02208ae4(arg + 0x42b0);
    int b = func_ov002_02208ad8(arg + 0x42b0, arg[0xb6]);
    func_ov002_0220a08c(arg + 0x4058, a, b, 2);
    arg[0xb4] = 0x14;
    func_ov002_02208098((void *) (arg), 7);
}

void func_ov122_0229f0dc(char *self, int second)
{
    func_ov002_02209740(self + 0x42b0, *(unsigned char *) (self + 0xb7), second);
    func_ov002_02208098((void *) (self), 22);
}

void func_ov122_0229f0a8(void *arg0)
{
    func_0200467c(0x28);
    ((unsigned char *) arg0)[0xb6] = 0xf;
    func_ov002_022096d8((char *) arg0 + 0x42b0, 1);
    func_ov002_02208098((void *) (arg0), 0x18);
    func_ov122_0229f2d0(arg0);
}

void func_ov122_0229f088(void *obj)
{
    int v;
    v = func_020984e8();
    v = func_02099734(v);
    v = func_02098ddc(v);
    func_02065db8(v, *(int *) ((char *) obj + 0xBC));
}

void func_ov122_0229f034(char *base, int a, int b)
{
    func_020a8874(base + 0x4150, (const void *) a, b);
    func_020a8a70(base + 0x40bc, base + 0x4150, 0, 0);
    if (func_020b4424(base + 0x40bc) != 0) {
        func_020a87e0(base + 0x4150, base + 0x40bc);
        func_0205182c(base + 0x4150, a, b);
    }
}

void func_ov122_0229effc(UnkStruct_0229effc *obj)
{
    func_ov122_0229f034((char *) obj, (int) (obj->data + 0x44), 0xa);
    func_ov122_0229f034((char *) obj, (int) (obj->data + 0xd8), 0x10);
    func_ov122_0229f034((char *) obj, (int) (obj->data + 0x58), 0x40);
}

int func_ov122_0229efe8(struct UnkStruct_0229efe8 *p, unsigned short mask)
{
    return (p->unk_A8 & mask) ? 1 : 0;
}

void func_ov122_0229efd8(unsigned short *param1, unsigned short param2)
{
    param1[0x54] |= param2;
}

void func_ov122_0229efc8(UnkStruct_0229efc8 *p, unsigned short mask)
{
    p->unk_A8 &= ~mask;
}
