/* func_0208c0f8 @ 0x0208c0f8, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xc];
    char unk_0C[0x20 - 0xc];
    unsigned int unk_20;
} UnkStruct_0208c0f8;

extern void *func_0208a1d0(void *p);
extern int func_0208a1b0(void *p, int x);
extern int func_0208a198(void *p, int x);
extern int func_0208aef0(UnkStruct_0208c0f8 *p);
extern int func_0208aeec(UnkStruct_0208c0f8 *p);
extern void func_02088df8(int a0, void *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11);

void func_0208c0f8(UnkStruct_0208c0f8 *s)
{
    void *saved;
    int v1, v2, v3, v4;
    int choice;

    if (s->unk_20 == 0) {
        return;
    }
    saved = func_0208a1d0((void *) &s->unk_0C);
    if (saved == 0) {
        return;
    }
    v1 = func_0208a1b0((void *) &s->unk_0C, -1);
    v2 = func_0208a198((void *) &s->unk_0C, -1);
    v3 = func_0208aef0(s);
    v4 = func_0208aeec(s);
    if ((s->unk_20 - 3) <= 2) {
        choice = 6;
    } else {
        choice = 5;
    }
    func_02088df8(0, saved, v3 + v1, v4 + v2, choice, -1, 0x1000, 0x1000, 0, -1, 0, 0);
}
