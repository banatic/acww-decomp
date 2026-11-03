/* music_queue: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02034dcc @ 0x02034dcc, 0x5c bytes, Thumb
 * func_02034dc8 @ 0x02034dc8, 0x2 bytes, Thumb
 * func_02034dac @ 0x02034dac, 0x1c bytes, Thumb
 * func_02034d84 @ 0x02034d84, 0x28 bytes, Thumb
 * func_02034d58 @ 0x02034d58, 0x2c bytes, Thumb
 * func_02034d28 @ 0x02034d28, 0x30 bytes, Thumb
 * func_02034d14 @ 0x02034d14, 0x12 bytes, Thumb
 * func_02034d00 @ 0x02034d00, 0x12 bytes, Thumb
 * func_02034cec @ 0x02034cec, 0x12 bytes, Thumb
 */

typedef struct {
    char pad_00[0x24c];
    char unk_24C;
    char pad_24D[0x2f4 - 0x24c - 1];
    unsigned char unk_2F4;
} UnkStruct_02034dcc;

extern int func_0203735c(void *);
extern int func_020b6840(int);
extern int func_020b6660(void);
extern int func_020b22b8(void);
extern void *func_0203734c(void *);
extern void func_0206e9bc(void *);
extern int func_020edf70(int);
extern __arm void *func_020ee660(void *);
extern void *func_02035510(void *);
extern unsigned char data_020da13c[];
extern unsigned char data_020da334[];
extern void *func_02035494(void *);
extern void func_020ee62c(void *);
extern void func_020edf54(void *p);
extern void func_02035404(void *ptr);
extern void func_02035344(int arg);
extern void func_0203539c(void *);

void *func_02034d84(void *obj);

void func_02034dcc(UnkStruct_02034dcc *s)
{
    if (func_0203735c(&s->unk_24C) != 0) {
        int r4 = 1;
        int a = func_020b6840(1);
        int b;
        if (a == 0) {
            r4 = 0;
        }
        b = func_020b6660();
        if (b != 0 && func_020b22b8() != 0) {
            r4 = 0;
        }
        if (s->unk_2F4 != 0) {
            r4 = 0;
        }
        if (r4 != 0) {
            func_0206e9bc(func_0203734c(&s->unk_24C));
        }
    }
}

void func_02034dc8(void *receiver) {}

void func_02034dac(void)
{
    int result;

    result = func_020edf70(0x348);
    if (result != 0) {
        func_02034d84((void *) result);
    }
}

void *func_02034d84(void *obj)
{
    func_020ee660(obj);
    *(void **) obj = (void *) data_020da13c;
    *(void **) obj = (void *) data_020da334;
    func_02035510((char *) obj + 0x50);
    return obj;
}

void *func_02034d58(void *this)
{
    *(int **) this = ((int *) data_020da334);
    func_02035494((char *) this + 0x50);
    *(int **) this = ((int *) data_020da13c);
    func_020ee62c(this);
    return this;
}

void *func_02034d28(void *p)
{
    *(void **) p = (void *) ((int *) data_020da334);
    func_02035494((char *) p + 0x50);
    *(void **) p = (void *) ((int *) data_020da13c);
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}

int func_02034d14(char *arg0)
{
    func_02035404(arg0 + 0x50);
    return 1;
}

int func_02034d00(int arg)
{
    func_02035344(arg + 0x50);
    return 1;
}

int func_02034cec(void *p)
{
    func_0203539c((char *) p + 0x50);
    return 1;
}
