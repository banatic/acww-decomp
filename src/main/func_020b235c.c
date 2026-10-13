/* func_020b235c @ 0x020b235c, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b3f58(int a);
extern int func_02073d90(void *p);
extern int func_02073918(void *p, int n);

struct nibble {
    unsigned char low : 4;
    unsigned char high : 4;
};

extern struct nibble data_021f4bac[];
extern void *data_020ccf94;
extern unsigned short data_020d1ebc[];

int func_020b235c(int idx)
{
    void *p;
    volatile unsigned short id;
    unsigned int ok;
    unsigned int v;

    p = data_020ccf94;
    if (func_02073d90(p) != 0) {
        if (func_02073918(p, 0) == 0) {
            goto ret0;
        }
    }
    id = data_020d1ebc[idx];
    ok = 0;
    v = id;
    if (v >= 0x5000 && v <= 0x5021) {
        ok = 1;
    }
    if (ok != 0) {
        return data_021f4bac[func_020b3f58(v)].low;
    }
ret0:
    return 0;
}
