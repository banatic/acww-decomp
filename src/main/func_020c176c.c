/* func_020c176c @ 0x020c176c, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);
extern int func_020b65c4(void);
extern int func_020c1608(void *, void *);

extern int data_021fbbdc;
extern unsigned char data_021fbbd8;

typedef struct {
    char pad_00[6];
    signed char unk_06;
    unsigned char unk_07;
} Param;

void func_020c176c(Param *p)
{
    struct UnkStruct_020c176c {
        int a;
        int b;
        int c;
    } local;

    local.a = 0;
    local.b = 0;

    if ((((int) (func_0209e474(&local), &local)), func_020b65c4()) == 0x3f) {
        data_021fbbdc = func_020c1608(p, &local);
        if (data_021fbbdc == 0) {
            data_021fbbd8 = p->unk_07;
        }
    } else {
        if (data_021fbbdc != 0) {
            unsigned char old = data_021fbbd8;
            if (func_020c1608(p, &local) != 0) {
                data_021fbbd8 = old;
            }
        } else {
            func_020c1608(p, &local);
        }
        data_021fbbdc = 0;
    }

    p->unk_06 = ((unsigned char *) &local)[2] - 6;
    if (p->unk_06 < 0) {
        p->unk_06 = p->unk_06 + 24;
    }
}
