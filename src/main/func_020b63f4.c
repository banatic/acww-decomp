/* func_020b63f4 @ 0x020b63f4, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} Src;

typedef struct {
    unsigned char tag;
    unsigned char flag;
    short half;
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
    unsigned char x;
    unsigned char y;
} Dst;

int func_020b63f4(Dst *dst, unsigned char val, const Src *src, unsigned int extra, short p1, unsigned char p2,
                  unsigned char p3)
{
    if (dst->tag == 0x3f) {
        dst->tag = val;
        dst->a = src->unk_00;
        dst->b = src->unk_04;
        dst->c = src->unk_08;
        dst->d = extra;
        dst->half = p1;
        dst->flag = 0;
        dst->x = p2;
        dst->y = p3;
        return 1;
    } else {
        return 0;
    }
}
