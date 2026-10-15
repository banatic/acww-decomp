/* func_02019144 @ 0x02019144, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x14];
    int unk_14;
    short unk_18;
    short unk_1A;
    unsigned short unk_1C;
} UnkStruct_02019144;

extern UnkStruct_02019144 *func_02019de4(char *a);
extern void func_0201b1a4(char *a, char *b, int c, int d, int e);
extern void func_0201aff4(char *a, int b);
extern void func_0201b350(char *a, int b);
extern void func_020123ec(int a, int b, int c);
extern void func_02019af0(char *a, int b);

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
