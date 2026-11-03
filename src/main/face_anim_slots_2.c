/* face_anim_slots_2: 21 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205db10 @ 0x0205db10, 0x28 bytes, Thumb
 * func_0205daf8 @ 0x0205daf8, 0x18 bytes, Thumb
 * func_0205dad8 @ 0x0205dad8, 0x20 bytes, Thumb
 * func_0205dad0 @ 0x0205dad0, 0x8 bytes, Thumb
 * func_0205dab8 @ 0x0205dab8, 0x18 bytes, Thumb
 * func_0205daac @ 0x0205daac, 0xc bytes, Thumb
 * func_0205da78 @ 0x0205da78, 0x34 bytes, Thumb
 * func_0205da74 @ 0x0205da74, 0x2 bytes, Thumb
 * func_0205d9ec @ 0x0205d9ec, 0x88 bytes, Thumb
 * func_0205d994 @ 0x0205d994, 0x58 bytes, Thumb
 * func_0205d978 @ 0x0205d978, 0x1c bytes, Thumb
 * func_0205d968 @ 0x0205d968, 0x10 bytes, Thumb
 * func_0205d950 @ 0x0205d950, 0x16 bytes, Thumb
 * func_0205d918 @ 0x0205d918, 0x36 bytes, Thumb
 * func_0205d908 @ 0x0205d908, 0xe bytes, Thumb
 * func_0205d8f4 @ 0x0205d8f4, 0x14 bytes, Thumb
 * func_0205d8ec @ 0x0205d8ec, 0x6 bytes, Thumb
 * func_0205d8e8 @ 0x0205d8e8, 0x2 bytes, Thumb
 * func_0205d8c4 @ 0x0205d8c4, 0x24 bytes, Thumb
 * func_0205d8c0 @ 0x0205d8c0, 0x4 bytes, Thumb
 * func_0205d8ac @ 0x0205d8ac, 0x14 bytes, Thumb
 */

typedef struct {
    int arr[9];
    unsigned short h1[18];
    unsigned short h2[18];
} UnkStruct_0205d994;

struct UnkStruct_0205d8f4 {
    char pad_00[0x24];
    short data[1][9];
};

typedef struct {
    unsigned char unk_00;
} UnkStruct_0205d8ec;

extern void func_0205c704(int);
extern int func_020e9abc(void *);

// placeholder, not used

extern unsigned char data_021c9aec[];
extern unsigned char data_021c9d7c[];
extern void func_0205c6e8(void);
extern int data_021c9d68;
extern int data_020dd6f0;
extern int func_02064328(int *obj, int *tbl, unsigned int hi, unsigned int raw);
extern unsigned char data_020cc65c[];
extern unsigned int func_020b65c4(void);
extern unsigned int func_020b5e04(unsigned int);
extern unsigned int func_020b5df8(unsigned int);
extern unsigned int func_02085f08(void);
extern unsigned int func_020e9968(unsigned int, unsigned int, unsigned int);
extern unsigned char *data_020ccf94;
extern void func_020e9b9c(void *ptr);
extern void func_0205d74c(int arg, int a, int b, int c, int d);

void func_0205d9ec(unsigned int *out);
void func_0205d994(UnkStruct_0205d994 *s);
void func_0205d8c0(unsigned char *p0, int p1);

void func_0205db10(int argument0)
{
    void *condition_value0;
    int *ptr;
    func_0205c704((int) argument0);
    func_0205d9ec((unsigned int *) ((void *) data_021c9d7c));
    ptr = (int *) data_021c9aec;
    if ((condition_value0 = (void *) (*ptr)) != 0) {
        func_020e9abc(condition_value0);
    }
}

void func_0205daf8(void)
{
    void *ptr;
    ptr = (void *) data_021c9d7c;
    func_0205d994((UnkStruct_0205d994 *) ptr);
    func_0205c6e8();
}

int *func_0205dad8(unsigned int raw)
{
    func_02064328(&data_021c9d68, &data_020dd6f0, raw >> 5, raw);
    return &data_021c9d68;
}

int func_0205dad0(void)
{
    return 280;
}

int func_0205dab8(void)
{
    int result;
    result = func_0205dad0();
    return result + 0x118;
}

unsigned char func_0205daac(unsigned int r0)
{
    return data_020cc65c[r0];
}

void func_0205da78(void *arg0)
{
    int i;
    int j;
    short *ptr;
    short value;

    value = 0x16f;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 2; j++) {
            ptr = (short *) ((char *) arg0 + (i * 2) + (j * 0x12) + 0x48);
            *ptr = value;
        }
    }
}

void func_0205da74(void *object) {}

void func_0205d9ec(unsigned int *out)
{
    unsigned int min_count, i, v, w, limit, j, size;
    unsigned int g;
    unsigned char byte;

    g = (*(unsigned int *) data_021c9aec);
    byte = data_020ccf94[0x6c];
    min_count = func_020b5e04((unsigned int) func_020b65c4());
    if (byte < min_count) {
        min_count = byte;
    }

    i = 0;
    while (i < min_count) {
        out[i] = func_020e9968(g, (unsigned int) func_0205dab8(), 4);
        i++;
    }

    if (min_count == 0) {
        min_count = 1;
    }

    v = func_020b5df8((unsigned int) func_020b65c4());
    w = func_02085f08();
    limit = v + w - min_count;

    size = 4;
    j = 4;
    while (j < limit + 4) {
        out[j] = func_020e9968(g, (unsigned int) func_0205dab8(), size);
        j++;
    }
}

void func_0205d994(UnkStruct_0205d994 *s)
{
    int i;
    int j;
    int zero = 0;
    unsigned short *p;
    unsigned short *q;

    for (i = 0; i < 9; i++) {
        s->arr[i] = 0;
        for (j = 0; j < 2; j++) {
            q = (unsigned short *) ((char *) s + i * 2 + j * 18);
            p = q;
            p += 0x48 / 2;
            *p = 0x16f;
            q[0x24 / 2] = zero;
        }
    }

    if ((*(void * *) data_021c9aec)) {
        func_020e9b9c((*(void * *) data_021c9aec));
    }
}

int func_0205d978(int *arr, int idx, int flag)
{
    if (flag == 1) {
        int v = arr[idx];
        return v + func_0205dad0();
    } else {
        return arr[idx];
    }
}

unsigned short func_0205d968(char *base, int x, int y)
{
    char *p = base + y * 18;
    p += x * 2;
    p += 72;
    return *(unsigned short *) p;
}

void func_0205d950(unsigned char *p, int i, int j, int v)
{
    unsigned char *q = p + j * 0x12;
    q = q + i * 2;
    *(short *) (q + 0x48) = (short) v;
}

int func_0205d918(int arg0, int arg1)
{
    int result;
    int i;
    int ret;

    result = (int) func_0205daac(arg1);
    for (i = 0; i < 9; i++) {
        ret = (int) func_0205d968((char *) arg0, i, result);
        if (ret == arg1) {
            return i;
        }
    }
    return 9;
}

unsigned short func_0205d908(void *param0, int param1, int param2)
{
    unsigned short *ptr;
    int offset;

    offset = param2 * 0x12;
    ptr = (unsigned short *) ((char *) param0 + offset);
    ptr += param1;
    return ptr[0x12];
}

void func_0205d8f4(struct UnkStruct_0205d8f4 *p, int col, int row, short value)
{
    p->data[row][col] = value;
}

void func_0205d8ec(UnkStruct_0205d8ec *p)
{
    p->unk_00 = 9;
}

void func_0205d8e8(void *object) {}

void func_0205d8c4(int arg, int argument1)
{
    func_0205d8c0((unsigned char *) arg, (int) argument1);
    func_0205d74c(arg, 0x16F, 0x16F, 0, 0);
}

void func_0205d8c0(unsigned char *p0, int p1)
{
    p0[0] = p1;
}

int func_0205d8ac(unsigned char *p, int x)
{
    return func_0205d978((int *) (((unsigned char *) data_021c9d7c)), (unsigned char) (*p), x);
}
