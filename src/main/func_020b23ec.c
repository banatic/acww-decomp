/* func_020b23ec @ 0x020b23ec, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b3f58(int a, int b);
extern int func_02073d90(void *p);
extern int func_02073918(void *p, int n);
extern void func_02073820(void *p);
extern void func_020737f0(void *p, void *q, int n);
extern void func_02073770(void *p, int a, int b);

typedef struct {
    unsigned char low : 4;
    unsigned char high : 4;
} NibbleByte;

extern NibbleByte data_021f4bac[];
extern void *data_020ccf94;

void func_020b23ec(int a, int b)
{
    int idx = func_020b3f58(a, b);
    void *p = data_020ccf94;

    if (func_02073d90(p) == 0 || func_02073918(p, 0) != 0 || func_02073918(p, 4) != 0) {
        NibbleByte *nf = &data_021f4bac[idx];
        nf->low = nf->low & ~(1 << b);
    } else {
        unsigned char c = (unsigned char) idx;
        void *obj = data_020ccf94;
        func_02073820(obj);
        func_020737f0(obj, &c, 1);
        func_02073770(obj, 0x24, 0);
    }
}
