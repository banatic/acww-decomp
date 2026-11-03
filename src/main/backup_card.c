/* backup_card: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02050b94 @ 0x02050b94, 0x46 bytes, Thumb
 * func_02050b78 @ 0x02050b78, 0x1c bytes, Thumb
 * func_02050af8 @ 0x02050af8, 0x7e bytes, Thumb
 * func_02050a84 @ 0x02050a84, 0x74 bytes, Thumb
 * func_02050a10 @ 0x02050a10, 0x74 bytes, Thumb
 * func_020509a8 @ 0x020509a8, 0x68 bytes, Thumb
 * func_02050974 @ 0x02050974, 0x32 bytes, Thumb
 * func_02050948 @ 0x02050948, 0x2c bytes, Thumb
 * func_02050920 @ 0x02050920, 0x28 bytes, Thumb
 * func_020508fc @ 0x020508fc, 0x24 bytes, Thumb
 * func_020508a0 @ 0x020508a0, 0x5c bytes, Thumb
 */

struct UnkStruct_02050af8 {
    unsigned int size;
    int value;
};

struct UnkStruct_02050a84 {
    unsigned int size;
    int result;
};

typedef struct {
    unsigned int limit;
    int handle;
} UnkStruct_02050a10;

struct UnkStruct_020509a8 {
    unsigned int unk_00;
    int unk_04;
};

struct UnkStruct_02050974 {
    int unk_00;
    int unk_04;
};

typedef struct {
    char pad_00[4];
    int unk_04;
} UnkStruct_02050948;

typedef struct {
    int a;
    int b;
} UnkStruct_020508a0;

extern int CARD_IsAvailable(void);
extern void CARD_Init(void);
extern int OS_GetLockID(void);
extern void func_0211ec44(unsigned short);
extern int func_0211f23c(int);
extern int CARD_GetBackupTotalSize(void);
extern void func_0211ec34(unsigned short);
extern void OS_ReleaseLockID(unsigned short);
extern int data_021c8188;
extern int data_020cb8e8;
extern int CARDi_RequestStreamCommand(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9);
extern int func_0211f230(void);
extern int CARD_GetResultCode(void);
extern int OS_GetTick(void);
extern void CARD_CancelBackupAsync(void);

int func_02050974(struct UnkStruct_02050974 *s);
void func_02050948(UnkStruct_02050948 *p);

void func_02050b94(int *out, int arg2, const void *metadata)
{
    int r;

    if (CARD_IsAvailable() == 0) {
        CARD_Init();
    }
    r = OS_GetLockID();
    func_0211ec44((unsigned short) r);
    func_0211f23c(arg2);
    *out = CARD_GetBackupTotalSize();
    func_0211ec34((unsigned short) r);
    OS_ReleaseLockID((unsigned short) r);
    ((unsigned char *) out)[8] = 4;
}

void func_02050b78(void)
{
    func_02050b94((int *) ((int) &data_021c8188), 4610, (const void *) ((int) &data_020cb8e8));
}

int func_02050af8(struct UnkStruct_02050af8 *p, int a, int b, int c)
{
    int result = 1;

    if ((unsigned) (a + c) > p->size) {
        return result;
    }

    p->value = OS_GetLockID();
    if (p->value == -3) {
        return result;
    }

    func_0211ec44((unsigned short) p->value);

    if (CARDi_RequestStreamCommand(b, a, c, 0, 0, 0, 7, 10, 2)) {
        result = 0;
    }

    func_0211ec34((unsigned short) p->value);
    OS_ReleaseLockID((unsigned short) p->value);

    p->value = -3;
    return result;
}

int func_02050a84(struct UnkStruct_02050a84 *p, int a, int b, int c)
{
    int ret = 1;

    if ((unsigned) (a + c) > p->size) {
        return ret;
    }

    p->result = OS_GetLockID();

    if (p->result == -3) {
        return ret;
    }

    func_0211ec44((unsigned short) p->result);
    CARDi_RequestStreamCommand(b, a, c, 0, 0, 1, 7, 10, 2);

    if (func_02050974((struct UnkStruct_02050974 *) p) == 3) {
        ret = 3;
    } else {
        func_02050948((UnkStruct_02050948 *) p);
    }

    return ret;
}

int func_02050a10(UnkStruct_02050a10 *s, unsigned int a, unsigned int b, unsigned int c)
{
    int success = 1;
    if ((c + b) > s->limit) {
        goto exit;
    }
    s->handle = OS_GetLockID();
    if (s->handle == -3) {
        goto exit;
    }
    func_0211ec44((unsigned short) s->handle);
    if (CARDi_RequestStreamCommand(c, a, b, 0, 0, 0, 6, success, 0) != 0) {
        success = 0;
    }
    func_0211ec34((unsigned short) s->handle);
    OS_ReleaseLockID((unsigned short) s->handle);
    s->handle = -3;
exit:
    return success;
}

int func_020509a8(struct UnkStruct_020509a8 *p, unsigned b, unsigned c, unsigned d)
{
    int ret = 1;
    if (d + c > p->unk_00) {
        goto end;
    }
    p->unk_04 = OS_GetLockID();
    if (p->unk_04 == -3) {
        goto end;
    }
    func_0211ec44((unsigned short) p->unk_04);
    CARDi_RequestStreamCommand(d, b, c, 0, 0, ret, 6, ret, 0);
    if (func_02050974((struct UnkStruct_02050974 *) p) == 3) {
        ret = 3;
    } else {
        func_02050948((UnkStruct_02050948 *) p);
    }
end:
    return ret;
}

int func_02050974(struct UnkStruct_02050974 *s)
{
    int r;
    if (s->unk_04 == -3) {
        return 4;
    }
    r = func_0211f230();
    if (r != 0) {
        goto L1;
    }
    return 3;
L1:
    if (CARD_GetResultCode() != 0) {
        goto L2;
    }
    return 0;
L2:
    return 1;
}

void func_02050948(UnkStruct_02050948 *p)
{
    if (p->unk_04 == ~2) {
        return;
    }
    func_0211ec34((unsigned short) p->unk_04);
    OS_ReleaseLockID((unsigned short) p->unk_04);
    p->unk_04 = ~2;
}

unsigned short func_02050920(unsigned short *data, int length)
{
    unsigned short sum = 0;

    if (length & 1) {
        goto done;
    }

    while (length != 0) {
        sum = (unsigned short) (sum + *data);
        data++;
        length -= 2;
    }

done:
    return sum;
}

unsigned short func_020508fc(int a, int b, unsigned short c)
{
    return (unsigned short) (((~(unsigned short) (func_02050920((unsigned short *) a, b) - c)) & 0xFFFF) + 1);
}

void func_020508a0(void)
{
    int t;
    if (func_02050974((struct UnkStruct_02050974 *) (((UnkStruct_020508a0 *) &data_021c8188))) == 3) {
        t = OS_GetTick();
        CARD_CancelBackupAsync();
        while (func_0211f230() == 0 && (unsigned int) (OS_GetTick() - t) < 0xcc8d)
            ;
        if ((*(UnkStruct_020508a0 *) &data_021c8188).b != -3) {
            func_0211ec34((unsigned short) (*(UnkStruct_020508a0 *) &data_021c8188).b);
            OS_ReleaseLockID((unsigned short) (*(UnkStruct_020508a0 *) &data_021c8188).b);
        }
    }
}
