/* func_ov004_02246cf4 @ 0x02246cf4, 0xf4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    Vec pos;
    int offset_x, offset_z, value, step;
    short first, second, angle, pad_22;
} Entry;
typedef struct {
    short unk_00, unk_02, unk_04, unk_06, unk_08, unk_0A, unk_0C;
    unsigned char unk_0E;
} State;
extern Entry data_ov004_022569ec[];
extern void VEC_Subtract(const void *, const void *, void *);
extern void VEC_Add(const void *, const void *, void *);
extern void func_020ea6e0(void *, int);
extern int func_0203c548(void *);
extern short func_0203c568(void *);
extern short func_0203c57c(void *);
extern void func_0203be6c(void *);
extern void func_01ffcbb0(void *, void *);
extern void func_0203bd84(void *, void *, int, int, int);
#define WORD(o) (*(int *) ((char *) self + (o)))
#define HALF(o) (*(short *) ((char *) self + (o)))
void func_ov004_02246cf4(void *self)
{
    State *b = (State *) ((char *) self + 0x21c);
    Vec offset, pos;
    int a, c, d;
    if (b->unk_04 == 1) {
        int z, x;
        Entry *entry = &data_ov004_022569ec[b->unk_02];
        WORD(0x110) = entry->pos.x;
        WORD(0x114) = entry->pos.y;
        WORD(0x118) = entry->pos.z;
        VEC_Subtract((char *) self + 0x110, (char *) self + 0x104, (char *) self + 0x110);
        if (func_0203c548(self) > 0x1400) {
            WORD(0x100) += entry->step;
        }
        HALF(0xfc) += entry->angle;
        b->unk_00 += entry->angle;
        z = entry->offset_z;
        x = entry->offset_x;
        offset.x = x;
        offset.y = 0;
        offset.z = z;
        VEC_Add((char *) self + 0x110, &offset, (char *) self + 0x110);
        func_020ea6e0(&offset, b->unk_00);
        VEC_Subtract((char *) self + 0x110, &offset, (char *) self + 0x110);
    }
    func_0203be6c(self);
    func_01ffcbb0(&pos, self);
    a = func_0203c57c(self);
    c = func_0203c568(self);
    d = func_0203c548(self);
    func_0203bd84(self, &pos, a, c, d);
}
