/* func_0208bad4 @ 0x0208bad4, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0208bad4 UnkStruct_0208bad4;
struct UnkStruct_0208bad4 {
    char pad_00[0xc];
    char sub[0x14];
    int unk_20;
    int unk_24;
    int unk_28;
};

extern void *func_0208a1d0(void *);
extern int func_0208aef0(UnkStruct_0208bad4 *);
extern int func_0208a1b0(void *, int);
extern int func_0208aeec(UnkStruct_0208bad4 *);
extern int func_0208a198(void *, int);
extern void func_02088df8(int, void *, int, int, int, int, int, int, int, int, int, int);

void func_0208bad4(UnkStruct_0208bad4 *p)
{
    void *v;
    int sum1;
    int shifted;
    int total;

    if (p->unk_20 == 0) {
        return;
    }
    v = func_0208a1d0(p->sub);
    if (v == 0) {
        return;
    }
    sum1 = func_0208aef0(p) + func_0208a1b0(p->sub, -1);
    shifted = (p->unk_28 + 0x800) >> 12;
    total = func_0208aeec(p) + func_0208a198(p->sub, -1) + p->unk_24 + shifted;
    func_02088df8(0, v, sum1, total, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
}
