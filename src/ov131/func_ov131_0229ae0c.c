/* func_ov131_0229ae0c @ 0x0229ae0c, 0xd8 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2c4];
    char unk_2C4;
} UnkStruct_0229ae0c;

extern int func_0206fca4(void);
extern void *func_020984e8(void);
extern int func_020992fc(int argument0);
extern int func_020983f0(int a);
extern int func_02099734(void *h);
extern int func_02098cf8(int a, int b);
extern int func_02098cc0(int a, int b, int c);
extern int func_02060d3c(void *p);
extern void func_ov130_02299de0(void *p, int a, int b, int c);

extern char data_021ebcd4[];

void func_ov131_0229ae0c(UnkStruct_0229ae0c *self)
{
    int hi;
    void *h;
    int q;
    int val;
    int kind;
    int cur;

    kind = func_0206fca4();
    h = func_020984e8();
    q = func_020992fc((int) h);

    switch (kind) {
        case 0x38:
            hi = 0x98967f;
            break;
        case 0x3a:
            hi = 0x63;
            break;
        case 0x36:
            hi = func_020983f0(q);
            break;
        default:
            hi = func_02098cf8(func_02099734(h), 1);
            break;
    }

    cur = 0;
    {
        char *p = data_021ebcd4;
        switch (kind) {
            case 0x34:
                cur = func_02060d3c(p);
                break;
            case 0x35:
                cur = func_020983f0(q);
                break;
            case 0x36:
                cur = func_02098cf8(func_02099734(h), 1);
                break;
        }
    }

    val = hi;
    switch (kind) {
        case 0x34:
            if (cur < hi) {
                val = cur;
            }
            break;
        case 0x35: {
            int d = 0x3b9ac9ff - cur;
            if (d < hi) {
                val = d;
            }
        } break;
        case 0x36: {
            int m = func_02098cc0(func_02099734(h), 1, 0);
            if (m < hi) {
                val = m;
            }
        } break;
    }

    func_ov130_02299de0(&self->unk_2C4, val, hi, cur);
}
