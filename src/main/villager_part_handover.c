/* villager_part_handover: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209af44 @ 0x0209af44, 0x3c bytes, Thumb
 * func_0209af2c @ 0x0209af2c, 0x18 bytes, Thumb
 * func_0209af04 @ 0x0209af04, 0x26 bytes, Thumb
 * func_0209aebc @ 0x0209aebc, 0x48 bytes, Thumb
 * func_0209ae70 @ 0x0209ae70, 0x4c bytes, Thumb
 */

typedef struct {
    char unk_00[0x10];
    char sub1[0x0c];
    int unk_1C;
    int unk_20;
    char sub2;
} UnkStruct_0209af44;

extern int func_02003780(void *);
extern void func_0209bd80(void *);
extern void func_02003738(void *);
extern void func_0209bd5c(void *);
extern void MI_CpuFill8(void *, int, int);
extern void func_0209bd7c(void *);
extern int func_02003750(void *);
extern int func_0209bd44(void *);
extern int func_02003704(void *);
extern int memcmp(void *, void *, int);
extern void func_0209bd30(void *s, unsigned char a, unsigned short *h, unsigned char b);
extern void func_0209bc24(int p1, int p2);
extern void func_02003728(void *a, void *b);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

void *func_0209af44(UnkStruct_0209af44 *arg)
{
    func_02003780(arg);
    func_0209bd80(arg->sub1);
    arg->unk_1C = 0;
    arg->unk_20 = 0;
    func_02003738(arg);
    func_0209bd5c(arg->sub1);
    arg->unk_1C = 0;
    arg->unk_20 = 0;
    MI_CpuFill8(&arg->sub2, 0, 1);
    return arg;
}

void *func_0209af2c(void *ptr)
{
    func_0209bd7c((char *) ptr + 0x10);
    func_02003750(ptr);
    return ptr;
}

void func_0209af04(void *arg0)
{
    void *p;
    int i;

    p = arg0;
    func_0209bd5c((char *) p + 0x10);
    func_02003738(p);
    i = 0;
    *(int *) ((char *) p + 0x1c) = i;
    *(int *) ((char *) p + 0x20) = i;
    MI_CpuFill8((char *) p + 0x24, 0, 1);
}

int func_0209aebc(void *r0, void *r1)
{
    int result;
    void *p = r0;
    void *q = r1;

    if (func_0209bd44((char *) p + 0x10) != 0) {
        if (func_02003704(q) != 0) {
            if (*(unsigned short *) q == *(unsigned short *) p) {
                if (memcmp((char *) q + 2, (char *) p + 2, 0xc) == 0) {
                    if (*(unsigned char *) ((char *) q + 0xf) == *(unsigned char *) ((char *) p + 0xf)) {
                        result = 1;
                        goto done;
                    }
                }
            }
        }
    }
    result = 0;
done:
    return result;
}

void func_0209ae70(unsigned int param1, unsigned int param2, unsigned int param3)
{
    unsigned short local_0;
    func_0209af04((void *) param1);
    local_0 = 0xfff1;
    func_0209bd30((void *) (param1 + 0x10), 0x15, &local_0, 0);
    func_0209bc24((int) (param1 + 0x10), 0);
    func_02003728((void *) param1, (void *) param2);
    MI_CpuCopy8((const void *) param3, (void *) (param1 + 0x1c), 8);
}
