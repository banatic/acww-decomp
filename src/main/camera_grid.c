/* camera_grid: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208c3c0 @ 0x0208c3c0, 0x2c bytes, Thumb
 * func_0208c3b8 @ 0x0208c3b8, 0x8 bytes, Thumb
 * func_0208c3a0 @ 0x0208c3a0, 0x18 bytes, Thumb
 * func_0208c354 @ 0x0208c354, 0x4c bytes, Thumb
 * func_0208c310 @ 0x0208c310, 0x42 bytes, Thumb
 * func_0208c308 @ 0x0208c308, 0x8 bytes, Thumb
 * func_0208c2ac @ 0x0208c2ac, 0x5c bytes, Thumb
 * func_0208c260 @ 0x0208c260, 0x4c bytes, Thumb
 * func_0208c21c @ 0x0208c21c, 0x42 bytes, Thumb
 */

typedef struct UnkStruct_0208c310 {
    char data[20];
} UnkStruct_0208c310;

typedef struct UnkStruct_0208c310_2 {
    char pad_00[12];
    UnkStruct_0208c310 arr[9];
} UnkStruct_0208c310_2;

typedef struct Elem {
    char data[20];
} Elem;

typedef struct UnkStruct_0208c21c {
    char pad_00[0xc];
    Elem arr[9];
} UnkStruct_0208c21c;

extern unsigned char data_020d0a84[];
extern unsigned char data_020d0a85[];
extern void func_0208a1f0(void *dst, void *src);
extern void func_0208a1ec(void *dst, void *src);
extern void *func_0208a144(void *dst);
extern char data_020d5b3c[];
extern void func_0208a0c8(UnkStruct_0208c310 *);
extern int func_0208a160(UnkStruct_0208c310 *);
extern int func_0208c5bc(void);
extern int func_020a7e50(void);
extern int func_020a7e44(void);
extern int func_0208c56c(void *p);
extern int func_0208c490(void *p);
extern void func_0208c42c(void *p);

void func_0208c354(void *self);
void func_0208c308(int p0);
void func_0208c260(void *arg0);

void func_0208c3c0(void *arg0)
{
    int val;
    int val2;
    int *piVar3;
    int *piVar4;

    piVar3 = (int *) ((int) arg0 + 0xc4);
    val = *piVar3;
    val2 = (int) (char) data_020d0a84[val * 2];
    piVar4 = (int *) ((int) arg0 + 0xc8);
    *piVar4 = val2;
    piVar3 = (int *) ((int) arg0 + 0xc4);
    val = *piVar3;
    val2 = (int) (char) data_020d0a85[val * 2];
    *(int *) ((int) arg0 + 0xcc) = val2;
    return;
}

void func_0208c3b8(int p0)
{
    *(int *) ((char *) (((int) (p0) + (192))) + (0)) = 0;
}

void func_0208c3a0(void *p)
{
    if (*((unsigned char *) p + 0xd4) != 0) {
        func_0208c354(p);
    }
}

void func_0208c354(void *self)
{
    int i;
    char *base;
    char *p;

    base = (char *) self;
    *(int *) (base + 0xc0) = 1;
    for (i = 0; i < 9; i++) {
        p = base + 0xc + i * 0x14;
        func_0208a1f0(p, data_020d5b3c + (i + 0xe) * 8);
        func_0208a1ec(p, (char *) 1);
        func_0208a144(p);
    }
}

void func_0208c310(UnkStruct_0208c310_2 *s)
{
    int flag = 1;
    int i = 0;
    int zero = i;
    for (; i < 9; i++) {
        UnkStruct_0208c310 *ptr = &s->arr[i];
        func_0208a0c8(ptr);
        if (func_0208a160(ptr) == 0) {
            flag = zero;
        }
    }
    if (flag) {
        func_0208c308((int) s);
    }
}

void func_0208c308(int p0)
{
    *(int *) ((char *) (((int) (p0) + (192))) + (0)) = 2;
}

void func_0208c2ac(unsigned char *self)
{
    unsigned char b = self[0xd4];
    if (b == 0) {
        func_0208c260(self);
        return;
    }
    if (func_0208c5bc() == 0) {
        int flag = 0;
        if (func_020a7e50() != 0) {
            if (func_0208c56c(self) != 0) {
                flag = 1;
            }
        } else {
            if (func_020a7e44() != 0) {
                if (func_0208c490(self) != 0) {
                    flag = 1;
                }
            }
        }
        if (flag != 0) {
            func_0208c42c(self);
        }
    }
}

void func_0208c260(void *arg0)
{
    int i;
    char *base;
    char *elem;

    *((int *) ((char *) arg0 + 0xc0)) = 3;
    i = 0;
    base = (char *) arg0;
    base += 0x0c;

    for (; i < 9; i++) {
        elem = base + i * 20;
        func_0208a1f0(elem, &((unsigned char *) data_020d5b3c)[(i + 0x17) * 8]);
        func_0208a1ec(elem, (void *) 1);
        func_0208a144(elem);
    }
}

void func_0208c21c(UnkStruct_0208c21c *s)
{
    int flag = 1;
    int zero = 0;
    int i;
    for (i = 0; i < 9; i++) {
        Elem *e = &s->arr[i];
        func_0208a0c8((UnkStruct_0208c310 *) e);
        if (func_0208a160((UnkStruct_0208c310 *) e) == 0) {
            flag = zero;
        }
    }
    if (flag) {
        func_0208c3b8((int) s);
    }
}
