/* func_0201e3d0 @ 0x0201e3d0, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0208150c(unsigned int);
extern unsigned int func_020036e8(unsigned int);
extern void func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern void func_0202d8f8(void *, void *, void *, unsigned int, int);

typedef struct {
    unsigned int a;
    unsigned int b;
} Pair;
extern Pair data_020d92b0;

typedef struct {
    unsigned int a;
    unsigned char b;
} Data020c8d18;
extern Data020c8d18 data_020c8d18;

void func_0201e3d0(unsigned char *self, unsigned char *out)
{
    unsigned int y;

    y = func_020036e8(func_0208150c(*(unsigned int *) (*(unsigned int *) (self + 0x100) + 0x830)));
    func_0202da38(self, self + 0x104, self + 0x122, 30, y, data_020c8d18.a, 1, 0, data_020c8d18.b);
    *(unsigned int *) out = (unsigned int) (self + 0x104);
    *(unsigned char *) (out + 4) = *(unsigned char *) (self + 0x122);
    func_0202d8f8(self, self + 0x12c, self + 0x128, *(unsigned int *) (*(unsigned int *) (self + 0x100) + 0x830), 0);
    *(Pair *) (self + 0xf8) = data_020d92b0;
}
