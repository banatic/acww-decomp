/* func_0208ab3c @ 0x0208ab3c, 0x1e8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a1d0(void *p);
extern int func_0208a824(void *p);
extern int func_0208a80c(void *p);
extern int func_0208a1b0(void *p, int v);
extern int func_0208a198(void *p, int v);
extern void func_02088df8(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, int a12);

typedef struct {
    unsigned char pad_00[0x34];
    int unk_34;
    unsigned char pad_38[0x44 - 0x38];
    int unk_44;
    unsigned char pad_48[0x56 - 0x48];
    unsigned char unk_56;
    unsigned char pad_57;
    unsigned char unk_58;
    unsigned char pad_59[0x5b - 0x59];
    unsigned char unk_5B;
} UnkStruct_0208ab3c;

void func_0208ab3c(UnkStruct_0208ab3c *p)
{
    int a1, a2, b, c;
    int r4, r6, r7, v28;

    if (p->unk_34 == 0) {
        return;
    }

    a1 = func_0208a1d0((char *) p + 0xc);
    a2 = func_0208a1d0((char *) p + 0x20);
    b = func_0208a824(p);
    c = func_0208a80c(p);

    r4 = b + func_0208a1b0((char *) p + 0xc, -1);
    r7 = c + func_0208a198((char *) p + 0xc, -1);
    r6 = b + func_0208a1b0((char *) p + 0x20, -1);
    v28 = c + func_0208a198((char *) p + 0x20, -1);

    if (p->unk_56 != 0) {
        func_02088df8(0, a1, r4, r7, -1, p->unk_44, 0x1000, 0x1000, 0, -1, 0, 0);
        if (p->unk_5B != 0) {
            func_02088df8(0, a2, r6, v28, -1, p->unk_44, 0x1000, 0x1000, 0, -1, 0, 0);
        }
        if (p->unk_58 != 0) {
            func_02088df8(0, a1, r4, r7, -1, p->unk_44, 0x1000, 0x1000, 0, 2, 0, 0);
            if (p->unk_5B != 0) {
                func_02088df8(0, a2, r6, v28, -1, p->unk_44, 0x1000, 0x1000, 0, 2, 0, 0);
            }
        }
    } else {
        func_02088df8(1, a1, r4, r7, -1, p->unk_44, 0x1000, 0x1000, 0, -1, 0, 0);
        if (p->unk_5B != 0) {
            func_02088df8(1, a2, r6, v28, -1, p->unk_44, 0x1000, 0x1000, 0, -1, 0, 0);
        }
        if (p->unk_58 != 0) {
            func_02088df8(1, a1, r4, r7, -1, p->unk_44, 0x1000, 0x1000, 0, 2, 0, 0);
            if (p->unk_5B != 0) {
                func_02088df8(1, a2, r6, v28, -1, p->unk_44, 0x1000, 0x1000, 0, 2, 0, 0);
            }
        }
    }
}
