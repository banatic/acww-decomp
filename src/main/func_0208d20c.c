/* func_0208d20c @ 0x0208d20c, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208a1d0(void *);
extern int func_0208a1b0(void *, int);
extern int func_0208a198(void *, int);
extern int func_0208aef0(void *);
extern int func_0208aeec(void *);
extern void func_02088df8(int, void *, int, int, int, int, int, int, int, int, int, int);

typedef struct {
    char pad_00[0xc];
    char sub[0x14];
    int unk_20;
    char pad_24[0xa8];
    int unk_CC;
} UnkStruct_0208d20c;

// Rounds a 20.12 fixed-point value to an integer.
static inline int fx_round(int v)
{
    return (v + 0x800) >> 12;
}

void func_0208d20c(UnkStruct_0208d20c *obj)
{
    if (obj->unk_20 != 0) {
        void *p = func_0208a1d0(obj->sub);
        if (p != 0) {
            int v1 = func_0208a1b0(obj->sub, -1);
            int v2 = func_0208a198(obj->sub, -1);
            int v3 = func_0208aef0(obj);
            int v4 = func_0208aeec(obj) + fx_round(obj->unk_CC);
            func_02088df8(0, p, v3 + v1, v4 + v2, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        }
    }
}
