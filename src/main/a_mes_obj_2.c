/* a_mes_obj_2: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02011fd8 @ 0x02011fd8, 0x3c bytes, Thumb
 * func_02011fc0 @ 0x02011fc0, 0x16 bytes, Thumb
 * func_02011fa4 @ 0x02011fa4, 0x1c bytes, Thumb
 * func_02011f88 @ 0x02011f88, 0x1c bytes, Thumb
 * func_02011f74 @ 0x02011f74, 0x14 bytes, Thumb
 * func_02011f54 @ 0x02011f54, 0x20 bytes, Thumb
 * func_02011f48 @ 0x02011f48, 0xc bytes, Thumb
 * func_02011f3c @ 0x02011f3c, 0xc bytes, Thumb
 * func_02011f2c @ 0x02011f2c, 0x10 bytes, Thumb
 * func_02011f1c @ 0x02011f1c, 0x10 bytes, Thumb
 * func_02011eec @ 0x02011eec, 0x30 bytes, Thumb
 * func_02011ed4 @ 0x02011ed4, 0x18 bytes, Thumb
 * func_02011ec8 @ 0x02011ec8, 0xc bytes, Thumb
 * func_02011ebc @ 0x02011ebc, 0xc bytes, Thumb
 * func_02011eb0 @ 0x02011eb0, 0xc bytes, Thumb
 * func_02011e48 @ 0x02011e48, 0x68 bytes, Thumb
 */

typedef unsigned int uint32_t;

struct UnkStruct_02011fd8 {
    char pad_00[0x48];
    uint32_t unk_48;       // 0x48
    uint32_t unk_4C;       // 0x4c
    char buffer[0x200];    // 0x50
    uint32_t unk_250;      // 0x250
    unsigned char unk_254; // 0x254
    unsigned char unk_255; // 0x255
};

typedef struct {
    unsigned char pad_00[0x250];
    unsigned int unk_250;
} UnkStruct_02011eec;

typedef struct {
    unsigned char pad_00[0x50];
    unsigned int unk_50;
} UnkStruct_02011eec_2;

extern void MI_CpuFill8(void *, int, unsigned int);
extern void func_02011bb0(int arg);
extern void func_02011b98(int arg);
extern void func_02039800(void);
extern unsigned char data_021c1284[];
extern void func_02011dd0(void *p1, int p2, int p3);
extern void func_02011d90(void *param1, void *param2, void *param3, void *param4);
extern unsigned char data_021c14c4[];
extern void func_02011d60(void *param1, void *param2);
extern void func_02011d30(int *param, int arg);
extern void func_020118a0(void *p, unsigned int v);
extern UnkStruct_02011eec_2 data_021c1484;
extern unsigned char data_020c80b8[];
extern int func_020b65c4(void);
void func_02011d28(void *);
int func_02011c28(void *, int);
void func_02011b38(void *, int);
int func_02011bc8(void *);
void func_02011af8(void *, int);
int func_0208ff98(void);

void func_02011e48(int a, int b);

struct UnkStruct_02011fd8 *func_02011fd8(struct UnkStruct_02011fd8 *ptr)
{
    ptr->unk_48 = 0;
    ptr->unk_4C = 0;
    ptr->unk_250 = 3;
    ptr->unk_254 = 0;
    ptr->unk_255 = 0;
    MI_CpuFill8(ptr->buffer, 0, 0x200);
    return ptr;
}

int func_02011fc0(int arg)
{
    func_02011bb0(arg);
    func_02011b98(arg);
    return arg;
}

void func_02011fa4(void)
{
    func_02011e48((int) ((void *) data_021c1284), 0);
    func_02039800();
}

void func_02011f88(void)
{
    unsigned int *addr = (unsigned int *) data_021c1284;
    func_02011e48((unsigned int) addr, 2);
    func_02039800();
}

void func_02011f74(int a, int b)
{
    func_02011dd0((void *) data_021c1284, a, b);
}

void func_02011f54(void *param1, void *param2, void *param3)
{
    func_02011d90((void *) data_021c1284, param1, param2, param3);
}

void func_02011f48(unsigned char value)
{
    data_021c14c4[0x15] = value;
}

unsigned char func_02011f3c(void)
{
    return (*(struct { unsigned char _pad[0x15]; unsigned char value; } *) data_021c14c4).value;
}

void func_02011f2c(void *param)
{
    func_02011d60((void *) data_021c1284, param);
}

void func_02011f1c(int arg)
{
    func_02011d30(((int *) data_021c1284), arg);
}

void func_02011eec(void)
{
    UnkStruct_02011eec *p = ((UnkStruct_02011eec *) data_021c1284);
    if (data_021c1484.unk_50 != 3) {
        func_020118a0(p, p->unk_250);
        p->unk_250 = 3;
    }
}

unsigned char func_02011ed4(void)
{
    unsigned char result;
    int index;

    index = func_020b65c4();
    result = data_020c80b8[index];
    return result;
}

unsigned char func_02011ec8(void)
{
    return data_021c14c4[0x14];
}

void func_02011ebc(void)
{
    unsigned char val = 1;
    data_021c14c4[0x14] = val;
}

void func_02011eb0(void)
{
    data_021c14c4[0x14] = 0;
}

void func_02011e48(int a, int b)
{
    void *p = ((char *) data_021c1284);

    func_02011d28(p);
    if (func_02011c28(((char *) data_021c1284), 4) != 0) {
        func_02011b38(p, b);
    }
    func_02011bb0((int) p);
    if (func_02011bc8(p) != 0) {
        func_02011af8(p, b);
    }
    func_02011b98((int) p);
    if ((int) func_02011ed4() == 2 && func_0208ff98() != 0) {
        func_02011d90((void *) a, (void *) 1, 0, (void *) b);
    }
}
