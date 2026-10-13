/* func_02025274 @ 0x02025274, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    void *unk_00;
    u8 unk_04;
} UnkStruct_02025274;
typedef struct {
    u32 unk_00;
    u8 unk_04;
} G8b;

extern void func_02024580(void *self);
extern void func_0207df18(void *a, unsigned short *newVal);
extern int func_0209bc40(unsigned char *p0);
extern unsigned int func_0202d9c4(unsigned int *r0);
extern void func_02081ac0(int p0, unsigned short *p1);
extern void func_02078710(int a, int b, int c);
extern unsigned int func_0208150c(unsigned int r0);
extern int func_020036e8(unsigned char *p0);
extern void func_0202da38(int p0, int p1, unsigned char *p2, int p3, int p4, int p5, int p6, int p7, int p8);

extern G8b data_020c8b10;
extern G8b data_020c8b00;

void func_02025274(u8 *self, UnkStruct_02025274 *out)
{
    const G8b *g = &data_020c8b10;
    void *pA;
    int r7;
    u32 v12c;

    pA = *(void **) (self + 0x100);
    r7 = *(int *) ((u8 *) pA + 0x830);
    func_02024580(self);

    if (*(u16 *) (self + 0x124) != 0xfff1) {
        func_0207df18((void *) r7, (u16 *) (self + 0x124));

        v12c = *(u32 *) (self + 0x12c);
        if (v12c != 0) {
            if (*(u32 *) (self + 0x128) != (u32) -1) {
                func_02081ac0((int) v12c, (u16 *) (self + 0x124));
                func_02078710(r7, *(int *) (self + 0x128), (int) (self + 0x124));
            }
        }
    }

    if (func_0209bc40((u8 *) func_0202d9c4((u32 *) self)) == 1) {
        g = &data_020c8b00;
    }

    pA = *(void **) (self + 0x100);
    r7 = *(int *) ((u8 *) pA + 0x830);

    func_0202da38((int) self, (int) (self + 0x104), (u8 *) (self + 0x122), 0x1e, func_020036e8((u8 *) func_0208150c((u32) r7)),
                  g->unk_00, g->unk_04, 0, 0);

    out->unk_00 = self + 0x104;
    out->unk_04 = *(self + 0x122);

    *(u16 *) (self + 0x15a) = 0x5f;
}
