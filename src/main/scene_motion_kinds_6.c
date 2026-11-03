/* scene_motion_kinds_6: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020191c8 @ 0x020191c8, 0x12 bytes, Thumb
 * func_020191b4 @ 0x020191b4, 0x12 bytes, Thumb
 * func_02019144 @ 0x02019144, 0x70 bytes, Thumb
 * func_02019098 @ 0x02019098, 0xac bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x14];
    int unk_14;
    short unk_18;
    short unk_1A;
    unsigned short unk_1C;
} UnkStruct_02019144;

extern int func_0201935c(int, int, int, int);
extern UnkStruct_02019144 *func_02019de4(char *a);
extern void func_0201b1a4(char *a, char *b, int c, int d, int e);
extern void func_0201aff4(char *a, int b);
extern void func_0201b350(char *a, int b);
extern void func_020123ec(int a, int b, int c);
extern void func_02019af0(char *a, int b);
extern volatile unsigned short data_020c80f8;
extern unsigned int data_020c81c4[];
extern unsigned short data_020c81a8[];
extern int func_0201afec(void *);
extern void func_02016764(void *, void *, unsigned int, unsigned short, int, int, int, int);
extern void func_02012444(int, unsigned short, int);
extern int func_0200442c(void *, unsigned short, int, int);

int func_020191c8(int a, int b)
{
    return func_0201935c(a, b, 1, 1);
}

int func_020191b4(int a, int b)
{
    return func_0201935c(a, b, 2, 2);
}

int func_02019144(char *p0, char *p1)
{
    UnkStruct_02019144 *a;
    int tmp;

    a = func_02019de4(p0);
    func_0201b1a4(p1 + 0x350, p1, 3, a->unk_1A, a->unk_1C);
    func_0201aff4(p1 + 0x350, a->unk_18);
    func_0201b350(p1 + 0x3aa, -2);
    tmp = *(int *) (p1 + 0x628);
    if (tmp != 0) {
        func_020123ec(tmp, a->unk_1C, 0);
    }
    *(int *) (p0 + 0xb0) = a->unk_14;
    func_02019af0(p0, 0);
    return 0;
}

void func_02019098(void *self, void *data)
{
    if (*(short *) ((char *) data + 0x8e) != func_0201afec((char *) data + 0x350)) {
        return;
    }
    if (*(int *) ((char *) self + 0xb0) >= 5) {
        *(int *) ((char *) self + 0xb0) = 0;
    }
    {
        unsigned short first = data_020c80f8;
        func_02016764((char *) data + 0x334, data, data_020c81c4[*(int *) ((char *) self + 0xb0)], data_020c80f8, 1, 0x1000, 0,
                      0);
        {
            int fld = *(int *) ((char *) data + 0x628);
            if (fld != 0) {
                func_02012444(fld, first, 0);
            }
        }
        func_0200442c((char *) data + 0x514, data_020c81a8[*(int *) ((char *) self + 0xb0)], 0x7f, 0);
        *(char *) ((char *) self + 0x98) = 1;
    }
}
