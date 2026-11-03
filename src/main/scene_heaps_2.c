/* scene_heaps_2: 30 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205c8f8 @ 0x0205c8f8, 0x18 bytes, Thumb
 * func_0205c8dc @ 0x0205c8dc, 0x1c bytes, Thumb
 * func_0205c8c4 @ 0x0205c8c4, 0x18 bytes, Thumb
 * func_0205c8a8 @ 0x0205c8a8, 0x1c bytes, Thumb
 * func_0205c814 @ 0x0205c814, 0x94 bytes, Thumb
 * func_0205c7f8 @ 0x0205c7f8, 0x1c bytes, Thumb
 * func_0205c7b4 @ 0x0205c7b4, 0x44 bytes, Thumb
 * func_0205c798 @ 0x0205c798, 0x1c bytes, Thumb
 * func_0205c760 @ 0x0205c760, 0x38 bytes, Thumb
 * func_0205c744 @ 0x0205c744, 0x1c bytes, Thumb
 * func_0205c704 @ 0x0205c704, 0x40 bytes, Thumb
 * func_0205c6e8 @ 0x0205c6e8, 0x1c bytes, Thumb
 * func_0205c6b0 @ 0x0205c6b0, 0x38 bytes, Thumb
 * func_0205c694 @ 0x0205c694, 0x1c bytes, Thumb
 * func_0205c65c @ 0x0205c65c, 0x38 bytes, Thumb
 * func_0205c640 @ 0x0205c640, 0x1c bytes, Thumb
 * func_0205c610 @ 0x0205c610, 0x30 bytes, Thumb
 * func_0205c5f4 @ 0x0205c5f4, 0x1c bytes, Thumb
 * func_0205c5bc @ 0x0205c5bc, 0x38 bytes, Thumb
 * func_0205c5a0 @ 0x0205c5a0, 0x1c bytes, Thumb
 * func_0205c560 @ 0x0205c560, 0x40 bytes, Thumb
 * func_0205c544 @ 0x0205c544, 0x1c bytes, Thumb
 * func_0205c4fc @ 0x0205c4fc, 0x48 bytes, Thumb
 * func_0205c4e0 @ 0x0205c4e0, 0x1c bytes, Thumb
 * func_0205c4a4 @ 0x0205c4a4, 0x3c bytes, Thumb
 * func_0205c488 @ 0x0205c488, 0x1c bytes, Thumb
 * func_0205c440 @ 0x0205c440, 0x48 bytes, Thumb
 * func_0205c424 @ 0x0205c424, 0x1c bytes, Thumb
 * func_0205c3e4 @ 0x0205c3e4, 0x40 bytes, Thumb
 * func_0205c3c8 @ 0x0205c3c8, 0x1c bytes, Thumb
 */

extern void *func_020ea1bc(int size, void *heap);
extern int data_021c9b00;
extern void func_020e9fc8(int arg);
extern int data_021c9afc; // at 0x021c9afc
extern int data_021c9af8;
extern int func_020b5e04(unsigned int);
extern int func_020b5df8(unsigned int);
extern int func_02085f08(void);
extern int func_0205cf44(void);
extern int func_0205cf3c(void);
extern int func_0205cf34(void);
extern int func_0203cfc0(void);
extern int data_021c9af4;
extern void *data_020ccf94;
extern unsigned int func_0205dd58(void);
extern __arm unsigned int func_020ea0e0(unsigned int, int);
extern unsigned int data_021c9af0;
extern int func_0205dab8(void);
extern unsigned char func_020b65c4(void);
extern int data_021c9aec;
extern unsigned int func_0205d208(void);
extern unsigned int data_021c9ae8;
extern unsigned int func_0205e700(void);
extern unsigned int data_021c9ae4;
extern unsigned int func_0205f958(void);
extern unsigned int data_021c9ae0;
extern unsigned int func_0205e0b0(void);
extern unsigned int data_021c9adc;
extern int func_0205f644(void);
extern int data_021c9ad8;
extern unsigned int func_0205dc3c(void);
extern unsigned int data_021c9ad4;
extern unsigned int func_0205f800(void);
extern unsigned int data_021c9ad0;
extern unsigned int func_0205f63c(void);
extern unsigned int data_021c9acc;
extern int func_020608fc(void);
extern int data_021c9ac8;

int func_0205c8f8(int size, int heapword)
{
    int result;
    result = (int) func_020ea1bc(size, (void *) heapword);
    data_021c9b00 = result;
    return result;
}

void func_0205c8dc(void)
{
    func_020e9fc8(data_021c9b00);
    data_021c9b00 = 0;
}

int func_0205c8c4(int size, int type)
{
    int result = (int) func_020ea1bc(size, (void *) type);
    data_021c9afc = result;
    return result;
}

void func_0205c8a8(void)
{
    func_020e9fc8((int) ((*(void * *) &data_021c9afc)));
    (*(void * *) &data_021c9afc) = 0;
}

void func_0205c814(void *arg)
{
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e;
    int min;
    int cond;
    cond = (*(unsigned char * *) &data_020ccf94)[0x6c];
    min = func_020b5e04((unsigned int) (int) func_020b65c4());
    if (((unsigned) cond) < ((unsigned) min)) {
        min = cond;
    }
    if (!min) {
        cond = 1;
    } else {
        cond = min;
    }
    e = func_020b5df8((unsigned int) (int) func_020b65c4());
    cond = (func_02085f08() + e) - cond;
    a += (func_0205cf44() + 3) & (~3);
    b += (func_0205cf3c() + 3) & (~3);
    c += (func_0205cf34() + 3) & (~3);
    {
        int sum = min + cond;
        a *= sum;
        d += a;
        b *= sum;
        d += b;
        c *= cond;
        data_021c9af8 = (int) func_020ea0e0(d + c, (int) arg);
    }
}

void func_0205c7f8(void)
{
    func_020e9fc8((int) ((*(void * *) &data_021c9af8)));
    (*(void * *) &data_021c9af8) = 0;
}

void func_0205c7b4(int param)
{
    int size = 0;
    int result = 0;
    int d, extra;

    size += (func_0203cfc0() + 3) & ~3;
    d = func_020b5df8((int) func_020b65c4());
    extra = func_02085f08();
    result += size * (d + extra + 1);
    data_021c9af4 = (int) func_020ea0e0(result, param);
}

void func_0205c798(void)
{
    func_020e9fc8((int) ((*(void * *) &data_021c9af4)));
    (*(void * *) &data_021c9af4) = 0;
}

unsigned int func_0205c760(int param)
{
    unsigned char count = ((unsigned char *) data_020ccf94)[0x6c];
    unsigned int size;
    unsigned int term;

    size = 0;
    term = size;
    term = term + ((func_0205dd58() + 3) & ~3u);
    size = size + term * count;
    return data_021c9af0 = func_020ea0e0(size, param);
}

void func_0205c744(void)
{
    func_020e9fc8((*(int *) &data_021c9af0));
    (*(int *) &data_021c9af0) = 0;
}

void func_0205c704(int arg)
{
    int acc = 0;
    int total = 0;
    int a, b;

    acc += ((func_0205dab8() + 3) & ~3);
    a = func_020b5df8((unsigned int) func_020b65c4());
    b = func_02085f08();
    acc *= (a + b);

    total += acc;
    data_021c9aec = (int) func_020ea0e0(total, arg);
}

void func_0205c6e8(void)
{
    func_020e9fc8((*(unsigned int *) &data_021c9aec));
    (*(unsigned int *) &data_021c9aec) = 0;
}

unsigned int func_0205c6b0(int param)
{
    unsigned char count = ((unsigned char *) data_020ccf94)[0x6c];
    unsigned int size;
    unsigned int term;

    size = 0;
    term = size;
    term = term + ((func_0205d208() + 3) & ~3u);
    size = size + term * count;
    return data_021c9ae8 = func_020ea0e0(size, param);
}

void func_0205c694(void)
{
    func_020e9fc8((int) ((*(void * *) &data_021c9ae8)));
    (*(void * *) &data_021c9ae8) = 0;
}

unsigned int func_0205c65c(int param)
{
    unsigned char count = ((unsigned char *) data_020ccf94)[0x6c];
    unsigned int size;
    unsigned int term;

    size = 0;
    term = size;
    term = term + ((func_0205e700() + 3) & ~3u);
    size = size + term * count;
    return data_021c9ae4 = func_020ea0e0(size, param);
}

void func_0205c640(void)
{
    func_020e9fc8((*(int *) &data_021c9ae4));
    (*(int *) &data_021c9ae4) = 0;
}

unsigned int func_0205c610(int param)
{
    unsigned char count = ((unsigned char *) data_020ccf94)[0x6c];
    unsigned int size;
    unsigned int term;

    size = 0;
    term = size;
    term = term + func_0205f958();
    size = size + term * count;
    return data_021c9ae0 = func_020ea0e0(size, param);
}

void func_0205c5f4(void)
{
    func_020e9fc8((int) ((*(void * *) &data_021c9ae0)));
    (*(void * *) &data_021c9ae0) = 0;
}

unsigned int func_0205c5bc(int param)
{
    unsigned char count = ((unsigned char *) data_020ccf94)[0x6c];
    unsigned int size;
    unsigned int term;

    size = 0;
    term = size;
    term = term + ((func_0205e0b0() + 3) & ~3u);
    size = size + term * count;
    return data_021c9adc = func_020ea0e0(size, param);
}

void func_0205c5a0(void)
{
    func_020e9fc8((*(int *) &data_021c9adc));
    (*(int *) &data_021c9adc) = 0;
}

void func_0205c560(int arg)
{
    int acc = 0;
    int total = 0;
    int a, b;

    acc += ((func_0205f644() + 3) & ~3);
    a = func_020b5df8((unsigned int) func_020b65c4());
    b = func_02085f08();
    acc *= (a + b);

    total += acc;
    data_021c9ad8 = (int) func_020ea0e0(total, arg);
}

void func_0205c544(void)
{
    func_020e9fc8(data_021c9ad8);
    data_021c9ad8 = 0;
}

unsigned int func_0205c4fc(int param)
{
    unsigned int acc = 0;
    unsigned int total = 0;
    unsigned int a;
    unsigned int sum;

    acc += ((func_0205dc3c() + 3) & ~3u);
    a = (unsigned int) func_020b5df8((unsigned int) func_020b65c4());
    sum = a + (unsigned int) func_02085f08();
    acc = (acc + 0x4b) & ~3u;
    acc *= sum;

    total += acc;
    return data_021c9ad4 = func_020ea0e0(total, param);
}

void func_0205c4e0(void)
{
    func_020e9fc8(data_021c9ad4);
    data_021c9ad4 = 0;
}

unsigned int func_0205c4a4(int param)
{
    unsigned char count = ((unsigned char *) data_020ccf94)[0x6c];
    unsigned int size;
    unsigned int term;

    size = 0;
    term = size;
    term = term + ((func_0205f800() + 3) & ~3u);
    term = (term + 0x4b) & ~3u;
    size = size + term * count;
    return data_021c9ad0 = func_020ea0e0(size, param);
}

void func_0205c488(void)
{
    func_020e9fc8((*(int *) &data_021c9ad0));
    (*(int *) &data_021c9ad0) = 0;
}

unsigned int func_0205c440(int param)
{
    unsigned int acc = 0;
    unsigned int total = 0;
    unsigned int a;
    unsigned int sum;

    acc += ((func_0205f63c() + 3) & ~3u);
    a = (unsigned int) func_020b5df8((unsigned int) func_020b65c4());
    sum = a + (unsigned int) func_02085f08();
    acc = (acc + 0x4b) & ~3u;
    acc *= sum;

    total += acc;
    return data_021c9acc = func_020ea0e0(total, param);
}

void func_0205c424(void)
{
    func_020e9fc8((*(int *) &data_021c9acc));
    (*(int *) &data_021c9acc) = 0;
}

void func_0205c3e4(int arg)
{
    int acc = 0;
    int total = 0;
    int a, b;

    acc += ((func_020608fc() + 3) & ~3);
    a = func_020b5df8((unsigned int) func_020b65c4());
    b = func_02085f08();
    acc *= (a + b);

    total += acc;
    data_021c9ac8 = (int) func_020ea0e0(total, arg);
}

void func_0205c3c8(void)
{
    func_020e9fc8((int) ((*(void * *) &data_021c9ac8)));
    (*(void * *) &data_021c9ac8) = 0;
}
