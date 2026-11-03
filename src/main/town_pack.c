/* town_pack: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a0140 @ 0x020a0140, 0x34 bytes, Thumb
 * func_020a0100 @ 0x020a0100, 0x40 bytes, Thumb
 * func_020a00fc @ 0x020a00fc, 0x4 bytes, Thumb
 * func_020a00c0 @ 0x020a00c0, 0x3c bytes, Thumb
 * func_020a008c @ 0x020a008c, 0x34 bytes, Thumb
 * func_020a0070 @ 0x020a0070, 0x1a bytes, Thumb
 * func_020a003c @ 0x020a003c, 0x34 bytes, Thumb
 * func_020a0030 @ 0x020a0030, 0xc bytes, Thumb
 */

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_020a0140;

typedef struct {
    char pad_00[0x64];
    unsigned int unk_64;
    char pad_68[0x58];
    unsigned int unk_C0;
    char pad_C4[0x1000];
    unsigned int unk_10C4;
    unsigned char unk_10C8;
} UnkStruct_020a008c;

extern int __arm MI_CompressLZ(const void *a, int b, int *c);
extern void __arm MI_CpuCopy8(const void *a, int *b, int c);
extern char data_021dc7a8[];
extern int func_020a13b8(void);
extern void MI_InitUncompContextLZ(void *buf, int ret, void *param4);
extern int MI_ReadUncompLZ8(void *buf, void *param8, int value);
extern int func_020a1350(void);
extern void *func_020a1338(void);
extern void OS_ExitThread(void);
extern void MI_CpuFill8(void *dest, unsigned char data, unsigned int size);
extern int OS_IsThreadTerminated(void *thread);
extern void OS_KillThread(int, int);
extern void OS_CreateThread(void *a, void *b, void *c, void *d, int e, int f);
extern void OS_WakeupThreadDirect(void *a);

void func_020a0140(UnkStruct_020a0140 *s)
{
    int result;
    result = MI_CompressLZ(data_021dc7a8, 0x000173fc, &s->unk_04);
    if (result == 0) {
        s->unk_00 = 0;
        MI_CpuCopy8(data_021dc7a8, &s->unk_04, 0x000173fc);
    } else {
        s->unk_00 = result;
    }
}

void func_020a0100(void *param)
{
    char buf[16];
    int ret = func_020a13b8();
    if (*(int *) param != 0) {
        MI_InitUncompContextLZ(buf, ret, (char *) param + 4);
        {
            char *p8 = (char *) param;
            p8 += 8;
            MI_ReadUncompLZ8(buf, p8, *(int *) param - 4);
        }
    } else {
        MI_CpuCopy8((const void *) ((char *) param + 4), (int *) ret, 0x000173fc);
    }
}

int func_020a00fc(int *p0)
{
    return p0[0];
}

void func_020a00c0(int flag)
{
    unsigned int b = (flag != 0);
    if (b > 0) {
        func_020a0140((UnkStruct_020a0140 *) ((void *) func_020a1350()));
    } else {
        func_020a0100((void *) func_020a1350());
    }
    {
        unsigned char *p = (unsigned char *) func_020a1338();
        p[0x10c8] = 1;
        OS_ExitThread();
    }
}

int func_020a008c(UnkStruct_020a008c *p)
{
    p->unk_C0 = 0x3039;
    p->unk_10C4 = 0x3039;
    p->unk_10C8 = 0;
    MI_CpuFill8(p, 0, 0xC0);
    p->unk_64 = 2;
    return 2;
}

void func_020a0070(int r0)
{
    int r4 = r0;
    if (OS_IsThreadTerminated((void *) r4) == 0) {
        OS_KillThread(r4, 0);
    }
}

void func_020a003c(void *obj, void *arg2)
{
    OS_CreateThread(obj, (void *) func_020a00c0, arg2, (char *) obj + 0x10c4, 0x1000, 30);
    OS_WakeupThreadDirect(obj);
}

unsigned char func_020a0030(unsigned char *ptr)
{
    return ptr[0x10C8];
}
