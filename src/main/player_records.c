/* player_records: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020985a0 @ 0x020985a0, 0x2c bytes, Thumb
 * func_02098580 @ 0x02098580, 0x20 bytes, Thumb
 * func_02098578 @ 0x02098578, 0x8 bytes, Thumb
 * func_02098554 @ 0x02098554, 0x24 bytes, Thumb
 * func_02098540 @ 0x02098540, 0x12 bytes, Thumb
 * func_02098530 @ 0x02098530, 0x10 bytes, Thumb
 * func_02098510 @ 0x02098510, 0x1e bytes, Thumb
 * func_020984fc @ 0x020984fc, 0x12 bytes, Thumb
 * func_020984e8 @ 0x020984e8, 0x14 bytes, Thumb
 * func_020984d4 @ 0x020984d4, 0x14 bytes, Thumb
 * func_0209847c @ 0x0209847c, 0x58 bytes, Thumb
 */

#define data_021dc7bc ((void *) 0x021dc7bc)

struct UnkStruct_020984e8 {
    char pad_00[0x68];
    void *unk_68;
};

struct UnkStruct_020984d4 {
    unsigned char pad_00[0x68];
    int unk_68;
};

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_02099ad0(void *);
extern void *func_02099bc8(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern int data_021d5738;
extern void func_02099a38(void *);
extern unsigned char func_02096284(void *);
extern struct UnkStruct_020984e8 *data_020ccf94;
extern int func_020988d8(void *);
extern int func_02098844(void *, void *);

int func_0209847c(void *p);

void *func_020985a0(void *arg)
{
    __cxa_vec_ctor((void *) (arg), 3, 0x249c, (((void (*)(void *)) func_02099bc8)), (((void (*)(void *)) func_02099ad0)));
    return arg;
}

int func_02098580(int arg)
{
    __cxa_vec_cleanup((void *) (arg), 3, 0x249C, (((void (*)(void *)) func_02099ad0)));
    return arg;
}

int func_02098578(void)
{
    return (int) &data_021d5738;
}

void func_02098554(void *arg0)
{
    int i;
    void *p;

    for (i = 0; i < 3; i++) {
        p = (void *) ((unsigned int) arg0 + (unsigned int) i * 0x249c);
        func_02099a38(p);
    }
}

void func_02098540(void)
{
    func_02098554((void *) func_02098578());
}

int func_02098530(int r0)
{
    if (r0 >= 4 && r0 < 7) {
        return 1;
    }
    return 0;
}

int func_02098510(int x)
{
    int r = -1;
    if (func_02098530(x) == 1) {
        r = x - 4;
    }
    return r;
}

int func_020984fc(void *p)
{
    return func_0209847c((void *) (unsigned int) func_02096284(p));
}

int func_020984e8(void)
{
    return func_020984fc(data_020ccf94->unk_68);
}

int func_020984d4(void)
{
    return (int) func_02096284((void *) ((*(struct UnkStruct_020984d4 **) &data_020ccf94)->unk_68));
}

int func_0209847c(void *p)
{
    int r = 0;

    if (func_020988d8(p) == 1) {
        if (data_021dc7bc != 0) {
            r = func_02098844(data_021dc7bc, p);
        }
    } else if (func_02098530((int) p) == 1) {
        if (func_02098578() != 0) {
            r = func_02098578();
            r = r + 0x249c * func_02098510((int) p);
        }
    }
    return r;
}
