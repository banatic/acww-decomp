/* func_020194fc @ 0x020194fc, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int pad_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int pad_14;
    short unk_18;
    short unk_1A;
    unsigned short unk_1C;
} UnkStruct_020194fc;

typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned int z;
} Vec3;

typedef struct {
    Vec3 unk_04;
    Vec3 unk_10;
} UnkStruct_020194fc_2;

extern void *func_02019de4(void *);
extern void func_0201b1a4(char *, char *, int, int, unsigned short);
extern void func_0201b044(char *, void *);
extern void func_0201afd4(char *, void *);
extern void func_0201aff4(char *, short);
extern void func_0201b350(char *, int);
extern void func_020123ec(unsigned int, unsigned short, int);
extern void func_02019af0(void *, int);
extern unsigned short data_020c80f8;

int func_020194fc(void *a, char *b)
{
    UnkStruct_020194fc *p = (UnkStruct_020194fc *) func_02019de4(a);
    UnkStruct_020194fc_2 local;
    int z1, x1, z2, x2;

    z1 = p->unk_08;
    x1 = p->unk_04;
    local.unk_04.x = x1;
    local.unk_04.y = 0;
    local.unk_04.z = z1;

    z2 = p->unk_10;
    x2 = p->unk_0C;
    local.unk_10.x = x2;
    local.unk_10.y = 0;
    local.unk_10.z = z2;

    func_0201b1a4(b + 0x350, b, 3, p->unk_1A, p->unk_1C);
    func_0201b044(b + 0x350, &local.unk_04);
    func_0201afd4(b + 0x350, &local.unk_10);
    func_0201aff4(b + 0x350, p->unk_18);
    func_0201b350(b + 0x3aa, -2);

    if (*(unsigned int *) (b + 0x628) != 0) {
        func_020123ec(*(unsigned int *) (b + 0x628), data_020c80f8, 0);
    }

    func_02019af0(a, 0);
    return 0;
}
