/* field_actor_16: 5 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_022102dc @ 0x022102dc, 0x78 bytes, Thumb
 * func_ov003_022102d0 @ 0x022102d0, 0xc bytes, Thumb
 * func_ov003_022101fc @ 0x022101fc, 0xd4 bytes, Thumb
 * func_ov003_022101a8 @ 0x022101a8, 0x54 bytes, Thumb
 * func_ov003_0221018c @ 0x0221018c, 0x1a bytes, Thumb
 */

struct UnkStruct_022102dc {
    unsigned char pad_00[0x5a0];
    int sub;
    unsigned char pad_5A4[0x24c];
    int unk_7F0;
    unsigned char pad_7F4[8];
    int unk_7FC;
    int unk_800;
};

typedef struct {
    unsigned int : 12;
    unsigned int field : 16;
    unsigned int : 4;
} Bitfield;

typedef struct UnkStruct_022101a8 {
    char pad_00[0x2d0];
    int unk_2D0;
    char pad_2D4[0x7f0 - 0x2d0 - 4];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f0 - 4];
    int unk_7FC;
    int unk_800;
} UnkStruct_022101a8;

extern int data_020ccf94;
extern int func_02073908(int, int);
extern int func_0203e168(void);
extern int func_02008258(struct UnkStruct_022102dc *, int);
extern int func_0200d4e8(struct UnkStruct_022102dc *, int, int, int);
extern void func_020ba35c(int);
extern void func_020109a0(struct UnkStruct_022102dc *, int b, int c, unsigned short d);
extern void func_0205eae0(int *, int, int, int);
extern int func_ov003_02210354(int a, int b, int c);
extern int func_0200faa8(void *p, int n);
extern void func_02010f5c(void *p);
extern void func_0200f2a0(void *p, int n, int *arr);
extern int func_02056f28(void *p, int n);
extern void func_0206026c(void *p, int n);
extern void func_02060428(void *p, int *arr);
extern int func_0200f328(void *p, int n);
extern unsigned int *func_0200f27c(void *p, int n);
extern int func_02056f94(int *p);
extern void func_020109fc(void *self, int a, int b, int c);
extern void func_02010d64(void *);

void func_ov003_022102dc(struct UnkStruct_022102dc *a, void *message, int previous)
{
    if (func_02073908(data_020ccf94, a->unk_800) != 0 && func_0203e168() == 0) {
        a->unk_7FC = func_02008258(a, a->unk_7F0);
        func_0200d4e8(a, 3, 1, -1);
        return;
    }
    func_020ba35c(a->unk_800);
    func_020109a0(a, 0x5f, 3, 0);
    func_0205eae0(&a->sub, 0x22, 3, 1);
}

void func_ov003_022102d0(int a, int b)
{
    func_ov003_02210354(a, 6, b);
}

void func_ov003_022101fc(void *p)
{
    int arr[3];
    int arr2[3];

    func_0200faa8(p, 0x400);
    func_02010f5c(p);

    if (*(int *) ((char *) p + 0x704) != 0x5f) {
        return;
    }

    arr[0] = *(int *) ((char *) p + 0x6f4);
    arr[1] = *(int *) ((char *) p + 0x6f8);
    arr[2] = *(int *) ((char *) p + 0x6fc);

    arr[1] += 0xb00;
    arr[2] += 0x300;

    if (((Bitfield *) ((char *) p + 0x2d8))->field < 0xb) {
        func_0200f2a0(p, 0x851, arr);
        return;
    } else {
        if (func_02056f28((char *) p + 0x2d0, 0xb) != 0) {
            func_0206026c((char *) p + 0x5c8, 9);
            arr2[0] = arr[0];
            arr2[1] = arr[1];
            arr2[2] = arr[2];
            func_02060428((char *) p + 0x5c8, arr2);
            func_0200f328(p, 0x852);
            func_0200f328(p, 0x853);
            func_0200f27c(p, 9);
        }
    }
}

void func_ov003_022101a8(UnkStruct_022101a8 *self)
{
    if (func_02056f94(&self->unk_2D0) == 0) {
        return;
    }
    func_020109fc(self, 0x60, 3, 3);
    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        return;
    }
    self->unk_7FC = func_02008258((struct UnkStruct_022102dc *) self, self->unk_7F0);
}

void func_ov003_0221018c(void *arg)
{
    func_ov003_022101fc(arg);
    func_02010d64(arg);
    func_ov003_022101a8((UnkStruct_022101a8 *) arg);
}
