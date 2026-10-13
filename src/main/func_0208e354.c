/* func_0208e354 @ 0x0208e354, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a1d0(void *p);
extern int func_0208aef0(void *self);
extern int func_0208a1b0(void *p, int x);
extern int func_0208aeec(void *self);
extern int func_0208a198(void *p, int x);
extern void func_02088df8(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11);

typedef struct {
    char pad_00[0x14];
    char unk_14[4];
    char pad_18[0x28 - 0x18];
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    char pad_38[0x7c - 0x38];
    unsigned char flag;
} UnkStruct_0208e354;

void func_0208e354(void *self)
{
    UnkStruct_0208e354 *s = (UnkStruct_0208e354 *) self;

    if (s->flag == 0) {
        return;
    }

    {
        int a = func_0208a1d0((char *) self + 0x14);
        int b = func_0208aef0(self);
        int v_total = s->unk_34 + (s->unk_28 + b) + func_0208a1b0((char *) self + 0x14, -1);
        int d = func_0208aeec(self);
        int v3_total = s->unk_30 + (s->unk_2C + d) + func_0208a198((char *) self + 0x14, -1);

        func_02088df8(0, a, v_total, v3_total, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}