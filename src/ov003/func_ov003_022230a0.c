/* func_ov003_022230a0 @ 0x022230a0, 0x148 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    char pad_08[0xcc - 8];
    int x;
    int y;
    int mode;
    char pad_D8[0xe0 - 0xd8];
    char buf[1];
} UnkStruct_022230a0;

extern int func_0204e414(void);
extern int func_0204f5e0(int, int, int, int, int, int);
extern int func_02045cec(int *, int);
extern void func_ov003_02222d68(UnkStruct_022230a0 *, int);
extern void func_02045ea8(int *, int, int);
extern void func_020044c0(char *, int, int, int);

void func_ov003_022230a0(UnkStruct_022230a0 *s, int flag)
{
    int h, r;
    int X, Y, ax, ay;
    int t1[2], t2[2], t3[2];

    h = func_0204e414();
    X = s->x;
    Y = s->y;
    ax = X >> 4;
    ay = Y >> 4;
    r = func_0204f5e0(h, ax, ay, X - (ax << 4), Y - (ay << 4), 0);
    switch (s->mode) {
        case 1:
            break;
        case 2:
        case 3:
            t1[0] = s->x;
            t1[1] = s->y;
            if (func_02045cec(t1, 0) >= 0) {
                func_ov003_02222d68(s, r);
                t2[0] = s->x;
                t2[1] = s->y;
                func_02045ea8(t2, s->unk_04, 0);
            }
            break;
        default:
            func_ov003_02222d68(s, r);
            t3[0] = s->x;
            t3[1] = s->y;
            func_02045ea8(t3, s->unk_04, 0);
            break;
    }
    if (flag == 0) {
        switch (s->mode) {
            case 0:
            case 2:
            case 3:
                func_020044c0(s->buf, 0x7dc, 0x7f, 0);
                break;
            case 1:
                func_020044c0(s->buf, 0x7d9, 0x7f, 0);
                break;
        }
    } else {
        switch (s->mode) {
            case 4:
            case 5:
            case 6:
            case 7:
                func_020044c0(s->buf, 0x855, 0x7f, 0);
                break;
            default:
                func_020044c0(s->buf, 0x7dd, 0x7f, 0);
                break;
        }
    }
    s->unk_00 = 1;
}
