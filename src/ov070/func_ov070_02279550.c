/* func_ov070_02279550 @ 0x02279550, 0x104 bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099670(int);
extern int func_0202ea80(int, int);
extern int func_02088b64(int);
extern int func_0208602c(void);
extern int func_02086108(int, int);

typedef struct {
    unsigned char pad_00[0xb0];
    int state;
    unsigned char *ptr;
} Object;

typedef struct {
    unsigned int word;
    unsigned char byte;
} Output;

typedef struct {
    unsigned char b[8];
} ByteEntry;
typedef struct {
    unsigned int w[2];
} WordEntry;

extern ByteEntry data_ov070_02279bac[];
extern WordEntry data_ov070_02279ba8[];

void func_ov070_02279550(Object *p, Output *out)
{
    int r6;
    int a;
    r6 = func_02099670(func_020984e8());
    if (func_0202ea80(7, 1) == 0) {
        p->state = 0;
    } else {
        if (func_0202ea80(8, 0) != 0) {
            if (func_0202ea80(9, 0) != 0) {
                p->state = 6;
            } else {
                if ((unsigned int) p->ptr[0x738] < 3u) {
                    p->state = 2;
                } else {
                    if ((unsigned int) func_02088b64(r6) >= 0x3du) {
                        p->state = 3;
                    } else {
                        p->state = 4;
                    }
                }
            }
        } else {
            p->state = 1;
        }
    }
    a = func_0208602c();
    if (func_02086108(a, 10) != 0) {
        if ((unsigned int) (p->state - 2) <= 2u) {
            p->state = 5;
        }
    }
    if (p->state < 0 || p->state >= 7) {
        return;
    }

    out->byte = data_ov070_02279bac[p->state].b[0];
    if (p->state == 2) {
        out->byte = p->ptr[0x738] + 0x4c;
        p->ptr[0x738]++;
    }
    out->word = data_ov070_02279ba8[p->state].w[0];
}
