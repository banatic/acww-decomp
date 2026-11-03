/* sky_weather_day_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020c181c @ 0x020c181c, 0x2 bytes, Thumb
 * func_020c1818 @ 0x020c1818, 0x2 bytes, Thumb
 * func_020c17f8 @ 0x020c17f8, 0x20 bytes, Thumb
 * func_020c17f0 @ 0x020c17f0, 0x8 bytes, Thumb
 * func_020c176c @ 0x020c176c, 0x84 bytes, Thumb
 */

typedef struct {
    char pad_00[6];
    signed char unk_06;
    unsigned char unk_07;
} Param;

extern unsigned char data_021fbbd8;
extern void func_0209df64(unsigned char *);
extern void func_0209e474(void *);
extern int func_020b65c4(void);
extern int func_020c1608(void *, void *);
extern int data_021fbbdc;

void func_020c176c(Param *p);

void func_020c181c(void *self) {}

void func_020c1818(void *self) {}

void func_020c17f8(char *ptr)
{
    data_021fbbd8 = 0;
    ptr[7] = 0;
    ptr[0] = 1;
    ptr[1] = 1;
    ptr[2] = 0;
    ptr[3] = 0;
    ptr[0] = 0;
    func_020c176c((Param *) ptr);
}

void func_020c17f0(unsigned char *argument0)
{
    func_0209df64((unsigned char *) argument0);
}

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
