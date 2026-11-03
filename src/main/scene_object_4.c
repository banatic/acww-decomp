/* scene_object_4: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201c450 @ 0x0201c450, 0xc bytes, Thumb
 * func_0201c444 @ 0x0201c444, 0xc bytes, Thumb
 * func_0201c438 @ 0x0201c438, 0xc bytes, Thumb
 * func_0201c400 @ 0x0201c400, 0x38 bytes, Thumb
 * func_0201c3f4 @ 0x0201c3f4, 0xc bytes, Thumb
 * func_0201c3dc @ 0x0201c3dc, 0x18 bytes, Thumb
 * func_0201c3b0 @ 0x0201c3b0, 0x2c bytes, Thumb
 * func_0201c390 @ 0x0201c390, 0x1e bytes, Thumb
 * func_0201c378 @ 0x0201c378, 0x18 bytes, Thumb
 * func_0201c350 @ 0x0201c350, 0x26 bytes, Thumb
 * func_0201c330 @ 0x0201c330, 0x20 bytes, Thumb
 * func_0201c314 @ 0x0201c314, 0x1c bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xEA];
    volatile unsigned short unk_EA;
} UnkStruct_0201c400;

typedef struct {
    unsigned char pad_00[0x638];
    int data;
} UnkStruct_0201c3f4;

struct UnkStruct_0201c3b0 {
    char pad_00[0x5c];
    char unk_5C;
    char pad_5D[0x8e - 0x5c - 1];
    short unk_8E;
};

extern int func_02055454(int);
extern void func_0203efb0(UnkStruct_0201c400 *a, int b);
extern short func_0200322c(char *ptr, int arg);
extern int func_020ea9e4(char *a, char *b);
extern int func_02096190(int);

int func_0201c450(int a)
{
    return func_02055454(a + 0xEC);
}

unsigned short func_0201c444(void *ptr)
{
    return *(unsigned short *) ((char *) ptr + 0x632);
}

void func_0201c438(char *base, unsigned short value)
{
    *(unsigned short *) (base + 0x632) = value;
}

void func_0201c400(UnkStruct_0201c400 *a, unsigned short *b)
{
    a->unk_EA = *b;
    func_0201c438((char *) a, (unsigned short) (a->unk_EA & 0x0FFF));
    func_0203efb0(a, (int) func_0201c444((void *) a));
}

void func_0201c3f4(UnkStruct_0201c3f4 *base, int value)
{
    base->data = value;
}

int func_0201c3dc(int r0)
{
    if (r0 < 0) {
        r0 = -r0;
    }
    if (r0 < 0x4000) {
        return 1;
    }
    return 0;
}

int func_0201c3b0(struct UnkStruct_0201c3b0 *param1, short *param2, int param3)
{
    *param2 = func_0200322c(&param1->unk_5C, param3);
    return func_0201c3dc((short) (*param2 - param1->unk_8E));
}

int func_0201c390(char *p1, char *p2)
{
    int result = 0;
    if (p2) {
        result = func_020ea9e4(p2 + 0x5c, p1 + 0x5c);
    }
    return result;
}

int func_0201c378(int a, int b)
{
    int c;
    int d;
    int e;

    c = a;
    d = b;
    e = func_02096190(d);
    return func_0201c390((char *) c, (char *) e);
}

int func_0201c350(int a, int b, int c)
{
    int result = 0;
    if (b != 0) {
        int val;
        val = func_0201c390((char *) a, (char *) b);
        if (val < 0) {
            val = -val;
        }
        if (val < c) {
            result = 1;
        }
    }
    return result;
}

int func_0201c330(int a, int b, int c)
{
    return func_0201c350(a, func_02096190(c), b);
}

int func_0201c314(void *r0, void *r1)
{
    int result = 0;
    if (r1 != 0) {
        result = (int) func_0200322c((char *) ((char *) r0 + 0x5c), (int) ((char *) r1 + 0x5c));
    }
    return result;
}
