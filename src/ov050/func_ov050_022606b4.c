/* func_ov050_022606b4 @ 0x022606b4, 0x64 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} InterData;
typedef struct {
    int unk_00;
    int pad_04;
    int unk_08;
} DataT;

extern int func_020984e8(void);
extern int func_02099640(int);
extern int func_02099020(int, int);
extern InterData *func_02095794(int);
extern DataT data_ov050_02265090;
extern void func_ov050_02263640(void *, int);
extern int func_0203e0a8(void *, int);

int func_ov050_022606b4(void *self)
{
    int id;
    InterData *ip;
    int ta, tb, tc;
    volatile struct {
        int a, b, c;
    } local;

    id = func_020984e8();
    func_02099640(id);

    if (func_02099020(id, 1) == 0) {
        goto fail;
    }

    ip = func_02095794(4);
    ta = ip->a;
    local.a = ta;
    tb = ip->b;
    local.b = tb;
    tc = ip->c;
    local.c = tc;

    if (tc >= data_ov050_02265090.unk_08) {
        goto fail;
    }
    if (ta <= data_ov050_02265090.unk_00) {
        goto fail;
    }

    func_ov050_02263640((char *) self + 0x658, 0x1e);
    func_0203e0a8(self, 0);
    return 1;
fail:
    return 0;
}
