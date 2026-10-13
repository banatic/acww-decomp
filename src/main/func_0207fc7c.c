/* func_0207fc7c @ 0x0207fc7c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a;
    unsigned int b;
} Pair;

extern Pair data_021d1330[];
extern Pair data_0213dd98;
extern unsigned int func_0209c2d4(unsigned char *flag, unsigned int b);

void func_0207fc7c(Pair *out, unsigned int unused, unsigned int b)
{
    unsigned char flag = 3;
    unsigned int ret = func_0209c2d4(&flag, b);

    if (flag == 0 && ret < 5) {
        *out = data_021d1330[ret];
    } else {
        *out = data_0213dd98;
    }
}
