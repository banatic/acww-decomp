/* func_02096614 @ 0x02096614, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    unsigned char pad[0x68];
    int unk_68;
} UnkStruct_02096614;
typedef struct {
    int unk_00;
    unsigned char pad[4];
    int unk_08;
} UnkStruct_02096614_3;
typedef struct {
    unsigned char pad[0x5c];
    UnkStruct_02096614_3 sub;
} UnkStruct_02096614_2;

extern UnkStruct_02096614 *data_020ccf94;
extern int func_02073908(UnkStruct_02096614 *g, int x);
extern UnkStruct_02096614_2 *func_02096718(int n);
extern unsigned char func_020b65c4(void);
extern int func_020966c4(int a);
extern int func_02096518(int *out, int a2, int a3);
extern int func_020966fc(int a);
extern void func_02077978(int p, int *a, int *b);
extern void func_02077a34(int a, unsigned char *b, int c);

int func_02096614(unsigned char *out0, int *out1, int *out2, int a4, int a5)
{
    int t, v, x, y;
    UnkStruct_02096614_2 *p;
    UnkStruct_02096614_3 *s;
    int q;

    if (a5 == 4) {
        a5 = data_020ccf94->unk_68;
    }
    if (func_02073908(data_020ccf94, a5) != 0) {
        p = func_02096718(4);
        if (p != 0) {
            s = &p->sub;
            *out0 = func_020b65c4();
            *out1 = p->sub.unk_00;
            *out2 = s->unk_08;
            return 1;
        }
        return 0;
    }
    t = func_020966c4(a5);
    if (t == 0) {
        return 0;
    }
    if (func_02096518(&v, a4, a5) == 0) {
        return 0;
    }
    if (v >= 0x93) {
        return 0;
    }
    q = func_020966fc(a5);
    if (q == 0) {
        return 0;
    }
    func_02077978(q, &x, &y);
    *out1 = x;
    *out2 = y;
    func_02077a34(t, out0, 0);
    return 1;
}
