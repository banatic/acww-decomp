/* func_020b8e10 @ 0x020b8e10, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_020b8e10_2;
typedef struct {
    unsigned char pad_00[0x7c];
    int unk_7C;
} UnkStruct_020b8e10;

extern int func_020b65c4(void);
extern int func_0203dff0(void);
extern int func_0203e21c(void);
extern int func_0203e190(void);
extern UnkStruct_020b8e10_2 *func_020682e0(int i);
extern int func_02070070(void);
extern int func_0206f53c(void);
extern void func_020b889c(void *p);
extern int data_020d2288[];
extern UnkStruct_020b8e10 data_021f6ba0;
extern unsigned char data_021f6b20[];

void func_020b8e10(int idx)
{
    int v;
    int res = 0;
    int ok;
    int c;
    int f;
    int t;
    UnkStruct_020b8e10_2 *e;

    v = func_020b65c4();
    ok = 0;
    if ((unsigned char) (v + 0xf4) <= 2) {
    } else if ((unsigned char) (v + 0xd2) <= 1) {
    } else {
        ok = 1;
    }
    if (ok != 0) {
        if (func_0203dff0() != 0 || func_0203e21c() != 0 || func_0203e190() != 0) {
            c = 1;
        } else {
            c = 0;
        }
        f = 0;
        if (c != 0) {
            e = func_020682e0(0);
            t = 0;
            if (e != 0 && e->unk_04 != 0) {
                t = 1;
            }
            if (func_02070070() != 0) {
                if (func_0206f53c() != 0) {
                    f = 1;
                } else {
                    res = 1;
                }
            } else {
                if (t != 0) {
                    res = 2;
                }
            }
        } else {
            if (func_02070070() != 0 && func_0206f53c() != 0) {
                f = 1;
            }
        }
        if (f != 0 && idx < 4) {
            res = data_020d2288[idx];
        }
    }
    if (data_021f6ba0.unk_7C != 0xa) {
        data_021f6ba0.unk_7C = res;
        if (res != 0) {
            func_020b889c(data_021f6b20);
        }
    }
}
