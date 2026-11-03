/* screen_sprite: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208af30 @ 0x0208af30, 0x14 bytes, Thumb
 * func_0208af24 @ 0x0208af24, 0xc bytes, Thumb
 * func_0208af0c @ 0x0208af0c, 0x18 bytes, Thumb
 * func_0208af00 @ 0x0208af00, 0xc bytes, Thumb
 * func_0208aef4 @ 0x0208aef4, 0xa bytes, Thumb
 * func_0208aef0 @ 0x0208aef0, 0x4 bytes, Thumb
 * func_0208aeec @ 0x0208aeec, 0x4 bytes, Thumb
 */

struct UnkStruct_0208af30 {
    int *p;
    int a;
    int b;
};

typedef struct {
    int unk_00;
    unsigned char *unk_04;
    unsigned char *unk_08;
} UnkStruct_0208aef4;

extern int data_020e20c8;
extern void func_020edb3c(void *);

void func_0208af30(struct UnkStruct_0208af30 *s)
{
    s->p = &data_020e20c8;
    s->a = 0x80;
    s->b = 0x60;
}

void func_0208af24(int **ptr)
{
    *ptr = &data_020e20c8;
}

void *func_0208af0c(void *obj)
{
    *(void **) obj = &data_020e20c8;
    func_020edb3c(obj);
    return obj;
}

void func_0208af00(int *ptr)
{
    *ptr = (int) &data_020e20c8;
}

void func_0208aef4(UnkStruct_0208aef4 *p, unsigned char *a, unsigned char *b)
{
    p->unk_04 = a + 0x80;
    p->unk_08 = b + 0x60;
}

int func_0208aef0(int *p0)
{
    return p0[1];
}

int func_0208aeec(int *p0)
{
    return p0[2];
}
