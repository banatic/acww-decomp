/* label_sprite_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208f210 @ 0x0208f210, 0x6 bytes, Thumb
 * func_0208f184 @ 0x0208f184, 0x8c bytes, Thumb
 */

typedef struct {
    char pad_00[0x1c];
    struct {
        int pad_00;
    } sub;
    char pad_20[0x24];
    int unk_44;
} UnkStruct_0208f184;

extern int func_0208a1b0(void *ptr, int val);
extern int func_0208a198(void *ptr, int val);

void func_0208f210(int *p, int a, int b)
{
    p[3] = a;
    p[4] = b;
}

void func_0208f184(UnkStruct_0208f184 *p, int *out1, int *out2)
{
    int a = 0;
    int b = 0;

    if (p->unk_44 == 2) {
        a = func_0208a1b0(&p->sub, -1) - func_0208a1b0(&p->sub, 0);
        b = func_0208a198(&p->sub, -1) - func_0208a198(&p->sub, 0);
    } else if (p->unk_44 == 3) {
        a = func_0208a1b0(&p->sub, 0) - func_0208a1b0(&p->sub, -1);
        b = func_0208a198(&p->sub, 0) - func_0208a198(&p->sub, -1);
    }

    *out1 = a;
    *out2 = b;
}
