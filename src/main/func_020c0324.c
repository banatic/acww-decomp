/* func_020c0324 @ 0x020c0324, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int v;
} UnkStruct_020c0324;
typedef struct {
    UnkStruct_020c0324 x;
    UnkStruct_020c0324 y;
    UnkStruct_020c0324 z;
} UnkStruct_020c0324_2;

extern UnkStruct_020c0324_2 data_021c67d0;
extern int data_020ca0e8;
extern int data_020ca0ec;
extern int _s32_div_f(int a, int b);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);

void func_020c0324(int *out, int px, int py, int flag)
{
    UnkStruct_020c0324_2 p;
    int d;
    int e;
    int n;
    int u;
    int w;
    int t;
    int s;

    p.x = data_021c67d0.x;
    p.y = data_021c67d0.y;
    p.z = data_021c67d0.z;
    e = data_020ca0e8;
    d = p.z.v - e;
    n = data_020ca0ec;
    u = _s32_div_f(n * 4, 2);
    w = FX_Div((p.x.v - n * 3) << 4, u);
    t = FX_Div(d, e << 2);
    if (w < -0x10000) {
        w = -0x10000;
    } else if (w > 0x10000) {
        w = 0x10000;
    }
    if (t < 0) {
        t = 0;
    } else if (t > 0x1000) {
        t = 0x1000;
    }
    t = t - 0x1000;
    t = FX_MulFunc(t, t);
    t = 0x1000 - t;
    w = -w;
    t = (t - 0x800) << 5;
    if (py < 0) {
        s = 0;
    } else if (py > 0xbf000) {
        s = 0xbf000;
    } else {
        s = py;
    }
    s = FX_Div(0xbf000 - s, 0xbf000);
    s = FX_MulFunc(t, s);
    py = py + s;
    out[0] = px + w;
    out[1] = py;
}
