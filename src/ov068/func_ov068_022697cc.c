/* func_ov068_022697cc @ 0x022697cc, 0x48 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201c390(int, int);
extern int func_0201c2b0(int, int);
extern short data_ov068_02278264;

struct S_ov068 {
    char pad_00[0xe4];
    int unk_E4;
};

int func_ov068_022697cc(int a, int b, int c)
{
    int flag = 0;
    int r;
    if (func_0201c390(b, ((struct S_ov068 *) a)->unk_E4) > c) {
        goto end;
    }
    r = func_0201c2b0(b, ((struct S_ov068 *) a)->unk_E4);
    if (r < -data_ov068_02278264) {
        goto end;
    }
    if (r > data_ov068_02278264) {
        goto end;
    }
    flag = 1;
end:
    return flag;
}
