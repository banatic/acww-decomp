/* func_020bed64 @ 0x020bed64, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[12];
    signed char unk_0C;
    signed char unk_0D;
    char pad_0E[2];
} Entry;

extern Entry data_020d2bac[];
extern int data_021f75b0;

extern void MI_CpuCopy8(void *dst, const void *src, int size);
extern int func_020bed04(void *a, int b);
extern void DC_FlushRange(void *a, int b);
extern void GX_LoadOBJPltt(void *a, int b, int c);
extern void GXS_LoadOBJPltt(void *a, int b, int c);
extern void func_020bec60(void *a, int b, int c);

void func_020bed64(void *a0, void *a1, unsigned int idx)
{
    Entry *e = &data_020d2bac[idx];
    int r6 = e->unk_0C;
    int r7;
    int ret;

    if (idx - 31 <= 1) {
        r6 += *(int *) a0;
    }

    r7 = (int) e->unk_0D << 5;

    MI_CpuCopy8((char *) a1 + 0x1048 + r6 * 32, (char *) a0 + 0x28, 32);

    ret = func_020bed04(a0, (int) e->unk_0D);

    DC_FlushRange((char *) a0 + 0x28, 32);
    GX_LoadOBJPltt((char *) a0 + 0x28, r7, 32);

    if (data_021f75b0 == 0) {
        GXS_LoadOBJPltt((char *) a0 + 0x28, r7, 32);
    }

    if (ret == 0) {
        func_020bec60(a0, (int) e->unk_0D, r6);
    }
}
