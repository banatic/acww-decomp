/* vector_2: 12 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020eaad0 @ 0x020eaad0, 0x38 bytes, ARM
 * func_020eaaa8 @ 0x020eaaa8, 0x28 bytes, ARM
 * func_020eaa6c @ 0x020eaa6c, 0x3c bytes, ARM
 * func_020eaa2c @ 0x020eaa2c, 0x40 bytes, ARM
 * func_020ea9e4 @ 0x020ea9e4, 0x48 bytes, ARM
 * func_020ea9c8 @ 0x020ea9c8, 0x1c bytes, ARM
 * func_020ea990 @ 0x020ea990, 0x38 bytes, ARM
 * func_020ea970 @ 0x020ea970, 0x20 bytes, ARM
 * func_020ea940 @ 0x020ea940, 0x30 bytes, ARM
 * func_020ea90c @ 0x020ea90c, 0x34 bytes, ARM
 * func_020ea8c8 @ 0x020ea8c8, 0x44 bytes, ARM
 * func_020ea88c @ 0x020ea88c, 0x3c bytes, ARM
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int x;
    int y;
    int z;
} Vec3_020ea9c8;

struct UnkStruct_020ea990 {
    int x;
    int y;
    int z;
};

struct S_020ea970 {
    int a;
    int pad_04;
    int b;
};

typedef struct {
    int x;
    int y;
    int z;
} Vec3_020ea90c;

extern int func_020eacf8(long long);
extern void VEC_CrossProduct(unsigned int, unsigned int, const unsigned int *);
extern void VEC_Normalize(const void *src, void *dst);

void func_020eaad0(void *dst, const void *src, int shift)
{
    int a, b, c;
    a = *(int *) src;
    b = *(int *) ((char *) src + 4);
    c = *(int *) ((char *) src + 8);
    *(int *) dst = a >> shift;
    *(int *) ((char *) dst + 4) = b >> shift;
    *(int *) ((char *) dst + 8) = c >> shift;
}

void func_020eaaa8(void *p, int shift)
{
    int *arr = (int *) p;
    arr[0] = arr[0] >> shift;
    arr[1] = arr[1] >> shift;
    arr[2] = arr[2] >> shift;
}

int func_020eaa6c(void *r0, void *r1)
{
    if (*(int *) r0 == *(int *) r1 && *(int *) ((char *) r0 + 4) == *(int *) ((char *) r1 + 4) &&
        *(int *) ((char *) r0 + 8) == *(int *) ((char *) r1 + 8)) {
        return 1;
    }
    return 0;
}

int func_020eaa2c(int *a, int *b)
{
    if (a[0] != b[0] || a[1] != b[1] || a[2] != b[2]) {
        return 1;
    }
    return 0;
}

int func_020ea9e4(Vec3 *a, Vec3 *b)
{
    int d;
    long long sum;

    d = a->x - b->x;
    sum = (long long) d * d;
    d = a->y - b->y;
    sum += (long long) d * d;
    d = a->z - b->z;
    sum += (long long) d * d;

    return func_020eacf8(sum);
}

int func_020ea9c8(Vec3_020ea9c8 *v)
{
    int x = v->x;
    int z = v->z;

    return func_020eacf8((long long) x * x + (long long) z * z);
}

int func_020ea990(struct UnkStruct_020ea990 *a, struct UnkStruct_020ea990 *b)
{
    int d;
    long long s;

    d = a->x - b->x;
    s = (long long) d * d;
    d = a->z - b->z;
    s += (long long) d * d;

    return func_020eacf8(s);
}

long long func_020ea970(struct S_020ea970 *p)
{
    int a = p->a;
    int b = p->b;

    return ((long long) a * a + (long long) b * b) >> 12;
}

long long func_020ea940(Vec3 *a, Vec3 *b)
{
    int dx = a->x - b->x;
    long long sum = (long long) dx * dx;
    int dz = a->z - b->z;
    sum += (long long) dz * dz;
    return sum >> 12;
}

int func_020ea90c(const Vec3_020ea90c *p, const Vec3_020ea90c *q)
{
    return (int) (((long long) p->x * q->x + (long long) p->z * q->z) >> 12);
}

void func_020ea8c8(unsigned int *dst, const unsigned int *src, unsigned int a, unsigned int b)
{
    VEC_CrossProduct(a, b, src);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

void func_020ea88c(void *dst, void *src)
{
    VEC_Normalize(src, src);
    *(unsigned int *) dst = *(unsigned int *) src;
    *(unsigned int *) ((char *) dst + 4) = *(unsigned int *) ((char *) src + 4);
    *(unsigned int *) ((char *) dst + 8) = *(unsigned int *) ((char *) src + 8);
}
