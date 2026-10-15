/* func_ov071_02278e40 @ 0x02278e40, 0xdc bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad[0xb0];
    int unk_B0;
} UnkStruct_02278e40;

typedef struct {
    int a;
    unsigned char b;
} UnkStruct_02278e40_2;

extern int func_020984e8(void);
extern int func_02099020(int, int);
extern int func_02099670(int);
extern void *func_02088a9c(void *record);
extern void func_0209df64(void *);
extern int func_0209dcdc(void *, const void *date);
extern int func_0202ea80(int, int);
extern int func_020644cc(int);

typedef struct {
    unsigned char b;
    char pad[7];
} Table1Entry;
typedef struct {
    int unk_00;
    int w1;
} Table2Entry;
extern const Table1Entry data_ov071_02279fc0[];
extern const Table2Entry data_ov071_02279fbc[];

void func_ov071_02278e40(UnkStruct_02278e40 *p, UnkStruct_02278e40_2 *q)
{
    void *x;
    int y;
    int r6 = 0;
    int t = func_020984e8();

    if (func_02099020(t, 0x17) != 0) {
        x = func_02088a9c((void *) func_02099670(t));
        func_0209df64(&y);
        if (func_0209dcdc(&y, x) < 1) {
            p->unk_B0 = 1;
        } else {
            if (func_02099020(t, 0x18) != 0) {
                if (func_0202ea80(0x28, r6) != 0) {
                    p->unk_B0 = 2;
                } else {
                    r6 = 1;
                }
            } else {
                if (func_0202ea80(0x28, r6) != 0) {
                    p->unk_B0 = r6;
                } else {
                    r6 = 1;
                }
            }
        }
    } else {
        if (func_0202ea80(0x28, r6) != 0) {
            p->unk_B0 = r6;
        } else {
            r6 = 1;
        }
    }

    if (p->unk_B0 >= 0 && p->unk_B0 < 3) {
        q->b = data_ov071_02279fc0[p->unk_B0].b;
        if (r6 != 0) {
            q->b = (unsigned char) (func_020644cc(5) + 0x28);
        }
        q->a = data_ov071_02279fbc[p->unk_B0].unk_00;
    }
}
