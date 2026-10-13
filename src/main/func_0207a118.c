/* func_0207a118 @ 0x0207a118, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0207a118 {
    unsigned char pad_00[0xc];
    long long v;
} UnkStruct_0207a118;

extern int func_0209dffc(long long *);
extern int func_0209e3ac(void *, long long *, int);
extern int func_0209e350(void *, void *);

int func_0207a118(UnkStruct_0207a118 *self, void *other)
{
    int r;
    int t;
    if (self->v == 0 || func_0209dffc(&self->v) != 0) {
        return 1;
    }
    r = 0;
    t = func_0209e3ac(other, &self->v, 0x3e);
    if (t == -1) {
        r = func_0209e350(other, &self->v);
    } else if (t == 1) {
        r = func_0209e350(&self->v, other);
    }
    if (r >= 0x3c) {
        return 1;
    }
    return 0;
}
