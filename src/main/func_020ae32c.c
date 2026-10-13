/* func_020ae32c @ 0x020ae32c, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021f49fc;
extern unsigned short data_021f49f8;
extern int data_021f4a14;

extern int func_0204e414(void);
extern void *func_0204f694(int a, int b);
extern void __register_global_object(void *a, void (*b)(void), void *c);
extern void func_020051b0(void);
extern int func_02037da8(void *a, void *b, void *c, void *d, void *e, int f);
extern void func_0209e474(void *);

typedef struct {
    unsigned int unk_00;
    unsigned int w1;
} Pair;

int func_020ae32c(void)
{
    int v1;
    int v2;
    Pair y;
    void *h;
    int t;

    t = func_0204e414();
    if (t != 0) {
        h = func_0204f694(t, 0x200);
        if (h != 0) {
            if ((data_021f49fc & 1) == 0) {
                data_021f49f8 = 0x5012;
                __register_global_object(&data_021f49f8, func_020051b0, &data_021f4a14);
                data_021f49fc |= 1;
            }
            if (func_02037da8(h, &v1, &v2, &data_021f49f8, &data_021f49f8, 0) != 0) {
                y.unk_00 = 0;
                y.w1 = 0;
                func_0209e474(&y);
                if (((unsigned char *) &y)[2] >= 6) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
