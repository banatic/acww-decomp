/* worker_thread_3: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020424b4 @ 0x020424b4, 0x4c bytes, Thumb
 * func_02042484 @ 0x02042484, 0x30 bytes, Thumb
 * func_02042458 @ 0x02042458, 0x2c bytes, Thumb
 * func_02042418 @ 0x02042418, 0x40 bytes, Thumb
 */

struct UnkStruct_020424b4 {
    char pad_00[0x20];
    void *unk_20;
};

struct R4Struct {
    char pad_00[0xC0];
    unsigned int unk_C0;
    unsigned int unk_C4;
    char pad_C8[0x1021];
    unsigned char unk_10E9;
};

struct Func02042458_Data {
    unsigned char pad_00[0x20];
    int unk_20;
};

extern struct UnkStruct_020424b4 data_021c779c;
extern void DC_FlushAll(void);
extern void func_0204714c(struct UnkStruct_020424b4 *base, void *a, void *b, unsigned int c, unsigned int d, unsigned int e);
extern void func_020ea584(unsigned int a, unsigned int b);
extern void OS_ExitThread(void);
extern void MI_CpuFill8(void *ptr, int a, int b);
extern int func_020e9948(void *param0, int param1);
extern void *data_021fbe94;
extern void MI_CpuCopy8(void *src, void *dst, int size);

void func_020424b4(void *p)
{
    struct R4Struct *r4;

    DC_FlushAll();

    r4 = (struct R4Struct *) data_021c779c.unk_20;

    func_0204714c(&data_021c779c, p, (char *) p + 8, *(unsigned int *) ((char *) p + 0x10),
                  *(unsigned char *) ((char *) p + 0x14), 1);

    func_020ea584(r4->unk_C0, r4->unk_C4);

    r4->unk_10E9 = 1;

    OS_ExitThread();
}

int func_02042484(void *ptr)
{
    ((char *) ptr)[0x10e8] = 0;
    ((char *) ptr)[0x10e9] = 0;
    ((char *) ptr)[0x10ea] = 0;
    MI_CpuFill8(ptr, 0, 0xc0);
    *(int *) ((char *) ptr + 0x64) = 2;
    return 2;
}

void func_02042458(void)
{
    int result;

    result = func_020e9948(data_021fbe94, 0x10ec);
    (*(struct Func02042458_Data *) &data_021c779c).unk_20 = result;
    if (result != 0) {
        func_02042484((void *) result);
    }
}

void func_02042418(unsigned char *p0, void *p1, void *p2, int p3, unsigned char p4)
{
    MI_CpuCopy8(p1, p0 + 0xc8, 8);
    MI_CpuCopy8(p2, p0 + 0xd0, 8);
    *(int *) (p0 + 0xd8) = p3;
    *(unsigned char *) (p0 + 0xdc) = p4;
    *(unsigned char *) (p0 + 0x10e8) = 1;
}
