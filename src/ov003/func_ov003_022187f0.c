/* func_ov003_022187f0 @ 0x022187f0, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02218890(void *, int *, int *, short *);
extern void func_ov003_022188d0(void *, int, int, int, int, int);

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    char pad_00[0x5c];
    Vec pos;
    char pad_68[0x26];
    short unk_8E;
} UnkStruct_022187f0;

void func_ov003_022187f0(UnkStruct_022187f0 *self, int a2)
{
    short c;
    Vec v;
    Vec *d;
    func_ov003_02218890((char *) self + 0x8f0, &v.x, &v.z, &c);
    v.y = self->pos.y;
    d = &self->pos;
    d->x = v.x;
    d->y = v.y;
    d->z = v.z;
    self->unk_8E = c;
    func_ov003_022188d0(self, v.x, v.z, c, 6, a2);
}
