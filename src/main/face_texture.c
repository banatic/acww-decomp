/* face_texture: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205dd98 @ 0x0205dd98, 0x28 bytes, Thumb
 * func_0205dd80 @ 0x0205dd80, 0x18 bytes, Thumb
 * func_0205dd60 @ 0x0205dd60, 0x20 bytes, Thumb
 * func_0205dd58 @ 0x0205dd58, 0x8 bytes, Thumb
 * func_0205dd54 @ 0x0205dd54, 0x2 bytes, Thumb
 * func_0205dd50 @ 0x0205dd50, 0x2 bytes, Thumb
 * func_0205dd10 @ 0x0205dd10, 0x40 bytes, Thumb
 * func_0205dce8 @ 0x0205dce8, 0x28 bytes, Thumb
 * func_0205dce0 @ 0x0205dce0, 0x6 bytes, Thumb
 * func_0205dcd8 @ 0x0205dcd8, 0x6 bytes, Thumb
 * func_0205dcd4 @ 0x0205dcd4, 0x2 bytes, Thumb
 * func_0205dccc @ 0x0205dccc, 0x8 bytes, Thumb
 * func_0205dcc8 @ 0x0205dcc8, 0x4 bytes, Thumb
 * func_0205dc94 @ 0x0205dc94, 0x34 bytes, Thumb
 * func_0205dc80 @ 0x0205dc80, 0x14 bytes, Thumb
 */

typedef struct {
    unsigned long a[64];
} UnkStruct_0205dce0;

typedef struct {
    unsigned char unk_00;
} UnkStruct_0205dcd8;

extern unsigned int func_0205c760(int);
extern int func_020e9abc(void *);
extern unsigned char data_021c9af0[];
extern unsigned char data_021c9e24[];
extern void func_0205c744(void);
extern int data_021c9e34;
extern int data_020dd704;
extern int func_02064328(int *obj, int *tbl, unsigned int hi, unsigned int raw);
extern int func_020e9968(int *p, int val, int n);
extern unsigned char *data_020ccf94;
extern void func_020e9b9c(int);
extern int func_02064af4(int a, int b, int c);

void func_0205dd10(int *out);
void func_0205dce8(int *arr);
void func_0205dcc8(unsigned char *p0, int p1);

void func_0205dd98(int val)
{
    int *ptr;

    func_0205c760(val);
    func_0205dd10((int *) ((unsigned int) data_021c9e24));
    ptr = (int *) data_021c9af0;
    val = *ptr;
    if (val != 0) {
        func_020e9abc((void *) val);
    }
}

void func_0205dd80(void)
{
    func_0205dce8((int *) ((unsigned int) data_021c9e24));
    func_0205c744();
}

int *func_0205dd60(unsigned int raw)
{
    func_02064328(&data_021c9e34, &data_020dd704, raw >> 5, raw);
    return &data_021c9e34;
}

int func_0205dd58(void)
{
    return 11824;
}

void func_0205dd54(void *self) {}

void func_0205dd50(void *object) {}

void func_0205dd10(int *out)
{
    int *p = (*(int **) data_021c9af0);
    unsigned int count = data_020ccf94[0x6c];
    unsigned int i;

    for (i = 0; i < count; i++) {
        out[i] = func_020e9968(p, func_0205dd58(), 4);
    }
}

void func_0205dce8(int *arr)
{
    int i;
    int j;
    i = 0;
    j = i;
    do {
        arr[i] = j;
        i++;
    } while (i < 4);
    if ((*(int *) data_021c9af0)) {
        func_020e9b9c((*(int *) data_021c9af0));
    }
}

unsigned long func_0205dce0(UnkStruct_0205dce0 *p, int i)
{
    return p->a[i];
}

void func_0205dcd8(UnkStruct_0205dcd8 *p)
{
    p->unk_00 = 4;
}

void func_0205dcd4(void *object) {}

void func_0205dccc(unsigned char *argument0, int argument1)
{
    func_0205dcc8((unsigned char *) argument0, (int) argument1);
}

void func_0205dcc8(unsigned char *p0, int p1)
{
    p0[0] = p1;
}

int func_0205dc94(unsigned char *p1, int p2)
{
    int a, b, c;
    a = (int) func_0205dce0((UnkStruct_0205dce0 *) ((void *) data_021c9e24), (unsigned char) (*p1));
    b = (int) func_0205dd60(p2);
    c = func_0205dd58();
    return func_02064af4(b, a, c);
}

unsigned long func_0205dc80(unsigned char *data)
{
    return func_0205dce0((UnkStruct_0205dce0 *) ((void *) data_021c9e24), (unsigned char) (*data));
}
