/* func_0201aff8 @ 0x0201aff8, 0x46 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Vec3 {
    int x, y, z;
};

struct Src {
    unsigned char pad_00[0x5c];
    struct Vec3 vec;
};

struct UnkStruct_0201aff8 {
    unsigned char pad_00[0x38];
    struct Vec3 unk_38;
    struct Vec3 unk_44;
    int threshold;
};

extern int func_020ea9e4(struct Vec3 *dst, struct Vec3 *src);

int func_0201aff8(struct UnkStruct_0201aff8 *self, struct Src *src, int cond)
{
    int v[3];
    int result;
    int ret;
    struct Vec3 *srcv;

    srcv = &src->vec;
    v[0] = src->vec.x;
    v[1] = srcv->y;
    v[2] = srcv->z;
    v[1] = 0;
    result = 0;

    if (cond) {
        ret = func_020ea9e4((struct Vec3 *) v, &self->unk_38);
    } else {
        ret = func_020ea9e4((struct Vec3 *) v, &self->unk_44);
    }

    if (ret < self->threshold) {
        result = 1;
    }

    return result;
}
