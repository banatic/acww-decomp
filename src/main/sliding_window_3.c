/* sliding_window_3: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208aa98 @ 0x0208aa98, 0x8 bytes, Thumb
 * func_0208aa90 @ 0x0208aa90, 0x8 bytes, Thumb
 * func_0208aa88 @ 0x0208aa88, 0x8 bytes, Thumb
 * func_0208aa80 @ 0x0208aa80, 0x8 bytes, Thumb
 * func_0208aa78 @ 0x0208aa78, 0x8 bytes, Thumb
 * func_0208aa70 @ 0x0208aa70, 0x8 bytes, Thumb
 * func_0208aa68 @ 0x0208aa68, 0x8 bytes, Thumb
 * func_0208aa60 @ 0x0208aa60, 0x6 bytes, Thumb
 * func_0208aa48 @ 0x0208aa48, 0x16 bytes, Thumb
 * func_0208aa40 @ 0x0208aa40, 0x8 bytes, Thumb
 * func_0208aa38 @ 0x0208aa38, 0x6 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[87];
    unsigned char unk_57;
} UnkStruct_0208aa38;

extern void func_02051a78(void *ptr, void *);

void func_0208aa98(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (88))) + (0)) = 1;
}

void func_0208aa90(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (88))) + (0)) = 0;
}

void func_0208aa88(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (89))) + (0)) = 1;
}

void func_0208aa80(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (90))) + (0)) = 1;
}

void func_0208aa78(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (90))) + (0)) = 0;
}

void func_0208aa70(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (91))) + (0)) = 1;
}

void func_0208aa68(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (91))) + (0)) = 0;
}

void func_0208aa60(int *p, int a, int b)
{
    p[15] = a;
    p[16] = b;
}

void func_0208aa48(void *arg, void *argument1)
{
    void *p = arg;
    func_02051a78((char *) p + 0x60, (void *) argument1);
    *(unsigned int *) ((char *) p + 0xc8) = 1;
}

void func_0208aa40(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (92))) + (0)) = 1;
}

void func_0208aa38(UnkStruct_0208aa38 *p, unsigned char v)
{
    p->unk_57 = v;
}
