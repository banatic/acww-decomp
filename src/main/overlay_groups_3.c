/* overlay_groups_3: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02070204 @ 0x02070204, 0x10 bytes, Thumb
 * func_020701e4 @ 0x020701e4, 0x20 bytes, Thumb
 * func_020701a8 @ 0x020701a8, 0x3c bytes, Thumb
 * func_02070150 @ 0x02070150, 0x58 bytes, Thumb
 * func_02070108 @ 0x02070108, 0x48 bytes, Thumb
 * func_020700cc @ 0x020700cc, 0x3c bytes, Thumb
 */

typedef struct UnkStruct_020701e4 {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned char *unk_08;
} UnkStruct_020701e4;

struct s_02070150 {
    char pad_00[8];
    void *unk_08;
};

extern int func_020e8ca8(void *arg, void *arg2);
extern unsigned char data_021cfca0[];
extern int func_020e8ce0(void *global, void *param);
extern void func_0206ff24(unsigned char byte);
extern struct {
    int a;
    int b;
    int c;
} data_021cfcb4;
extern int func_0206ff48(int);
extern unsigned char data_020df328[2];
extern unsigned short data_020df590[];
extern void *data_021cfc84;
void func_0206f5b0(void);
int func_0202f134(unsigned short, void *, unsigned char, int);
extern int *data_020df5ec[];
extern void func_0204f934(int);
extern void func_0206ff98(int);
extern void func_0204f8ec(int);
extern void func_0206ff74(int);
extern void func_0206ff00(int);

int func_020700cc(int x);

void func_02070204(void *arg)
{
    void *r1 = arg;
    void *r0 = (void *) data_021cfca0;
    void *r3 = (void *) 0x020e8ca8;
    func_020e8ca8(r0, r1);
}

void func_020701e4(UnkStruct_020701e4 *param)
{
    func_020e8ce0(((unsigned int *) data_021cfca0), param);
    func_0206ff24(*(param->unk_08 + 0x90));
}

void func_020701a8(void)
{
    if (data_021cfcb4.a || data_021cfcb4.b || data_021cfcb4.c) {
        unsigned char i;
        for (i = 0; i < 46; i++) {
            if (func_0206ff48(i)) {
                func_020700cc(i);
            }
        }
    }
}

int func_02070150(void)
{
    unsigned char b;
    void *r4;
    if (data_020df328[0] != 3) {
        return 0;
    }
    if ((*(struct s_02070150 **) data_021cfca0) != 0) {
        r4 = (*(struct s_02070150 **) data_021cfca0)->unk_08;
    } else {
        r4 = data_021cfc84;
    }
    func_0206f5b0();
    b = data_020df328[1];
    if (func_0202f134(data_020df590[b], r4, b, 4) == 0) {
        return 0;
    }
    data_020df328[0] = 1;
    return 1;
}

int func_02070108(void)
{
    int *arr;
    int i;

    if (data_020df328[0] != 2) {
        return 0;
    }
    arr = data_020df5ec[data_020df328[1]];
    for (i = 0; arr[i] != -1; i++) {
        func_0204f934(arr[i]);
    }
    data_020df328[0] = 3;
    func_0206ff98(data_020df328[1]);
    return 1;
}

int func_020700cc(int x)
{
    int *p = data_020df5ec[x];
    int i;

    for (i = 0; p[i] != -1; i++) {
        func_0204f8ec(p[i]);
    }
    func_0206ff74(x);
    func_0206ff00(x);
    return 1;
}
