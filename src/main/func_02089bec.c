/* func_02089bec @ 0x02089bec, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a000(void *dest, int a, int b, int c, int d, int e, unsigned char f, int g);

typedef struct {
    char pad_00[0x40];
    int unk_40;
    int unk_44;
    int unk_48;
} Dst;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} Src;

void func_02089bec(Dst *dest, const Src *src, int a, int b, int c, int d, int e, unsigned char f, int g)
{
    dest->unk_40 = src->unk_00;
    dest->unk_44 = src->unk_04;
    dest->unk_48 = src->unk_08;
    func_0208a000(dest, a, b, c, d, e, f, g);
}
