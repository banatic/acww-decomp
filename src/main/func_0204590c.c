/* func_0204590c @ 0x0204590c, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02044878(int);
extern void func_02042ff8(int, int *);
extern void func_02042e10(void *, int *);
extern unsigned short data_020ca658[];
extern int data_021c80b4;

typedef struct {
    int unk_00;
    int pad_04[4];
    int unk_14;
    int unk_18;
} UnkStruct_0204590c;
typedef struct {
    unsigned char unk_00;
    unsigned char b1 : 5;
    unsigned char b1h : 3;
    unsigned char pad_02[4];
    unsigned short unk_06;
} UnkStruct_0204590c_2;

int func_0204590c(UnkStruct_0204590c_2 *p, UnkStruct_0204590c *q)
{
    volatile unsigned short t = 0xfff1;
    int ret = 0;

    t = p->unk_06;
    switch (p->b1) {
        case 19: {
            int ok = 0;
            unsigned short lo = t;
            unsigned short hi = t;
            if (hi >= 0x1518 && lo <= 0x151c) {
                ok = 1;
            }
            if (ok) {
                p->unk_06 = data_020ca658[lo - 0x1518];
            } else {
                switch (lo) {
                    case 0x1548:
                        p->unk_06 = 0xc8;
                        break;
                    case 0x151d:
                        p->unk_06 = 0x26;
                        break;
                    case 0x151e:
                        p->unk_06 = 0x5d;
                        break;
                }
            }
            break;
        }
        case 15: {
            int v[2];
            int r = func_02044878(q->unk_00);
            v[0] = q->unk_14;
            v[1] = q->unk_18;
            func_02042ff8(r, v);
            ret = 1;
            break;
        }
        case 12:
        case 13:
        case 23:
            ret = 1;
            break;
        case 14: {
            int w[2];
            w[0] = q->unk_14;
            w[1] = q->unk_18;
            func_02042e10(&data_021c80b4, w);
            break;
        }
    }
    return ret;
}
