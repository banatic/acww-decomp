/* func_020595fc @ 0x020595fc, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    char pad_00[0x5c];
    Vec pos;
    char pad_68[0x8e - 0x68];
    short unk_8E;
} Target;
typedef struct {
    char pad_00[0xcc];
    Target *targets[2];
} UnkStruct_020595fc;
extern void func_020ea6e0(Vec *p, int v);
extern void VEC_Add(Vec *p, Vec *q, Vec *r);
void func_020595fc(UnkStruct_020595fc *base, Vec *dest, Vec *src, unsigned int idx)
{
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
    if (idx < 2 && base->targets[idx] != 0) {
        func_020ea6e0(dest, base->targets[idx]->unk_8E);
        VEC_Add(dest, &base->targets[idx]->pos, dest);
    }
}
