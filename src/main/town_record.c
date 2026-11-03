/* town_record: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204cc34 @ 0x0204cc34, 0x62 bytes, Thumb
 * func_0204cc24 @ 0x0204cc24, 0x10 bytes, Thumb
 * func_0204cc14 @ 0x0204cc14, 0x10 bytes, Thumb
 * func_0204cc04 @ 0x0204cc04, 0x10 bytes, Thumb
 * func_0204cbe0 @ 0x0204cbe0, 0x24 bytes, Thumb
 * func_0204cbc0 @ 0x0204cbc0, 0x20 bytes, Thumb
 * func_0204cb90 @ 0x0204cb90, 0x2e bytes, Thumb
 * func_0204cb50 @ 0x0204cb50, 0x40 bytes, Thumb
 * func_0204cb48 @ 0x0204cb48, 0x8 bytes, Thumb
 * func_0204cb2c @ 0x0204cb2c, 0x1a bytes, Thumb
 * func_0204cafc @ 0x0204cafc, 0x30 bytes, Thumb
 * func_0204cae8 @ 0x0204cae8, 0x14 bytes, Thumb
 * func_0204cac0 @ 0x0204cac0, 0x26 bytes, Thumb
 * func_0204cab4 @ 0x0204cab4, 0xc bytes, Thumb
 * func_0204ca8c @ 0x0204ca8c, 0x28 bytes, Thumb
 */

typedef union {
    int words[2];
    unsigned char bytes[8];
} Buf;

typedef struct {
    unsigned short unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} UnkStruct_0204cbe0;

typedef struct {
    unsigned short unk_00;
    char pad_02[10];
} Entry;

typedef struct {
    unsigned short unk_00;
    char unk_02;
    int unk_04;
    int unk_08;
} UnkStruct_0204cb50;

typedef struct {
    char pad_00[0x58];
    void *array[1];
} UnkStruct_0204cafc;

extern int func_0209de88(int, int, int);
extern int func_020644cc(int);
extern void func_0209e29c(int, int);
extern unsigned char data_021f3a20[];
extern void func_0203fb80(int *, int *, int);
extern char func_0209dee8(void);
extern int func_020984d4(void);
extern void func_0209df64(int);
extern int func_0209dcdc(void *, void *);
extern signed char data_021f3a08[];
extern int data_020ccf94;
extern int func_02073d90(int);

int func_0204cb90(int a, int b);

void func_0204cc34(unsigned char *self, unsigned char *p)
{
    Buf buf;
    int firstResult;
    int loopResult;
    int counter;

    buf.words[0] = 0;
    buf.words[1] = 0;

    firstResult = func_0209de88(p[2], p[1], p[0]);

    counter = 7;
    do {
        loopResult = func_020644cc(counter);
    } while (loopResult == 1 || loopResult == 2);

    buf.words[0] = 0;
    buf.words[1] = 0;
    buf.bytes[5] = p[2];
    buf.bytes[4] = p[1];
    buf.bytes[3] = p[0];
    func_0209e29c((int) &buf, (7 - firstResult) + loopResult);

    self[0xa] = buf.bytes[5];
    self[9] = buf.bytes[4];
    self[8] = buf.bytes[3];
}

void func_0204cc24(char *p)
{
    int i = 0;
    char c = i;
    for (; i < 10; i++) {
        *(p + i + 12) = c;
    }
}

void func_0204cc14(char *p)
{
    int i = 0;
    char val = (char) i;
    do {
        (p + i)[0x16] = val;
        i++;
    } while (i < 0xB);
}

int func_0204cc04(int index)
{
    return (int) (data_021f3a20 + index * 12);
}

void func_0204cbe0(void *object)
{
    UnkStruct_0204cbe0 *p;
    int i;

    p = (UnkStruct_0204cbe0 *) func_0204cc04(0);
    for (i = 0; i < 4; i++) {
        p->unk_00 = 99;
        p->unk_04 = 1;
        p->unk_08 = 1;
        p++;
    }
}

void func_0204cbc0(int argument0, int argument1)
{
    int result;
    void *ptr;

    result = func_0204cb90((int) argument0, (int) argument1);
    if (result >= 0) {
        ptr = (void *) func_0204cc04(result);
        *(unsigned short *) ptr = 0x63;
        *(unsigned int *) ((char *) ptr + 4) = 1;
        *(unsigned int *) ((char *) ptr + 8) = 1;
    }
}

int func_0204cb90(int a, int b)
{
    int result = -1;
    int i;
    Entry *p;

    p = (Entry *) func_0204cc04(0);
    for (i = 0; i < 4; i++) {
        if (b == p->unk_00) {
            result = i;
            break;
        }
        p++;
    }
    return result;
}

int func_0204cb50(int a, int b)
{
    int r;
    UnkStruct_0204cb50 *p;

    r = func_0204cb90(a, b);
    if (r >= 0) {
        goto done;
    }
    r = func_0204cb90(a, 99);
    if (r < 0) {
        goto done;
    }
    p = (UnkStruct_0204cb50 *) func_0204cc04(r);
    p->unk_00 = (unsigned short) b;
    func_0203fb80(&p->unk_04, &p->unk_08, b);
    p->unk_02 = func_0209dee8();
done:
    return r;
}

int func_0204cb48(int p0, int p1)
{
    return ((int) (((int) (p0) + (88))) + ((p1 << 2)));
}

void func_0204cb2c(int arg)
{
    int ret1 = func_020984d4();
    int ret2 = func_0204cb48(arg, ret1);
    func_0209df64(ret2);
}

int func_0204cafc(UnkStruct_0204cafc *param)
{
    int ret = 0;
    int idx;
    struct {
        int a, b;
    } obj;

    idx = func_020984d4();
    func_0209df64((int) (&obj));
    if (func_0209dcdc(&obj, &param->array[idx]) != 0) {
        ret = 1;
    }
    return ret;
}

int func_0204cae8(void)
{
    int result = 0;
    if (data_021f3a08[21] >= 15) {
        result = 1;
    }
    return result;
}

void func_0204cac0(unsigned char *p, int a, int b)
{
    if (a == 4) {
        int c = *(signed char *) (p + 0x21);
        if (c < 0) {
            *(signed char *) (p + 0x21) = 1;
        } else {
            *(signed char *) (p + 0x21) = c + b;
        }
    } else {
        *(signed char *) (p + 0x21) = -1;
    }
}

unsigned char func_0204cab4(void)
{
    return ((unsigned char *) data_021f3a08)[0x17];
}

void func_0204ca8c(unsigned int param)
{
    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }
    if (param >= 0x17) {
        param = 0x16;
    }
    ((unsigned char *) data_021f3a08)[0x17] = (unsigned char) param;
}
