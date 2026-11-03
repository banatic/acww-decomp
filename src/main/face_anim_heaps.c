/* face_anim_heaps: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205dc58 @ 0x0205dc58, 0x28 bytes, Thumb
 * func_0205dc40 @ 0x0205dc40, 0x18 bytes, Thumb
 * func_0205dc3c @ 0x0205dc3c, 0x4 bytes, Thumb
 * func_0205dc38 @ 0x0205dc38, 0x2 bytes, Thumb
 * func_0205dc34 @ 0x0205dc34, 0x2 bytes, Thumb
 * func_0205dbb8 @ 0x0205dbb8, 0x7c bytes, Thumb
 * func_0205db80 @ 0x0205db80, 0x38 bytes, Thumb
 * func_0205db78 @ 0x0205db78, 0x6 bytes, Thumb
 * func_0205db70 @ 0x0205db70, 0x6 bytes, Thumb
 * func_0205db6c @ 0x0205db6c, 0x2 bytes, Thumb
 * func_0205db4c @ 0x0205db4c, 0x20 bytes, Thumb
 * func_0205db38 @ 0x0205db38, 0x14 bytes, Thumb
 */

typedef struct {
    unsigned long a[64];
} UnkStruct_0205db78;

typedef struct {
    unsigned char unk_00;
} UnkStruct_0205db70;

extern unsigned int func_0205c4fc(int);
extern int func_020e9abc(void *);
extern unsigned char data_021c9ad4[];
extern unsigned char data_021c9df4[];
extern void func_0205c4e0(void);
extern unsigned int data_020ccf94;
extern int func_020b65c4(void);
extern int func_020b5e04(unsigned int);
extern int func_020b5df8(unsigned int);
extern int func_02085f08(void);
extern int func_020ea0e0(int, int);
extern void func_020e9b9c(void *p);

void func_0205dbb8(int *r6);
void func_0205db80(void **arr);

void func_0205dc58(int argument0)
{
    void *condition_value0;
    void *ptr;
    int *global_ptr;

    func_0205c4fc((int) argument0);
    func_0205dbb8((int *) ((void *) data_021c9df4));
    global_ptr = (int *) data_021c9ad4;
    if ((condition_value0 = (void *) (*global_ptr)) != 0) {
        func_020e9abc(condition_value0);
    }
}

void func_0205dc40(void)
{
    (((int) (func_0205db80((void **) (((int *) data_021c9df4))), ((int *) data_021c9df4))), func_0205c4e0());
}

int func_0205dc3c(void)
{
    return 80;
}

void func_0205dc38(void *self) {}

void func_0205dc34(void *object) {}

void func_0205dbb8(int *r6)
{
    unsigned int r4;
    unsigned int r5;
    int r7;
    unsigned char r5b;
    int r0v;

    r7 = *((int *) data_021c9ad4);
    r5b = *((unsigned char *) ((*((int *) (&data_020ccf94))) + 0x6c));
    r4 = func_020b5e04((unsigned int) func_020b65c4());
    if (r5b < r4) {
        r4 = r5b;
    }
    r5 = 0;
    while (r5 < r4) {
        r0v = func_0205dc3c();
        r6[r5] = func_020ea0e0(r0v, r7);
        r5++;
    }

    if (r4 == 0) {
        r4 = 1;
    }
    r5 = func_020b5df8((unsigned int) func_020b65c4());
    r0v = func_02085f08();
    r4 = (r5 + r0v) - r4;
    r4 = r4 + 4;
    r5 = 4;
    while (r5 < r4) {
        r0v = func_0205dc3c();
        r6[r5] = func_020ea0e0(r0v, r7);
        r5++;
    }
}

void func_0205db80(void **arr)
{
    int i;

    for (i = 0; i < 9; i++) {
        if (arr[i] != 0) {
            func_020e9b9c(arr[i]);
            arr[i] = 0;
        }
    }
    if ((*(void * *) data_021c9ad4) != 0) {
        func_020e9b9c((*(void * *) data_021c9ad4));
    }
}

unsigned long func_0205db78(UnkStruct_0205db78 *p, int i)
{
    return p->a[i];
}

void func_0205db70(UnkStruct_0205db70 *p)
{
    p->unk_00 = 9;
}

void func_0205db6c(void *object) {}

void func_0205db4c(unsigned char *ptr, unsigned char value)
{
    func_020e9b9c((void *) func_0205db78((UnkStruct_0205db78 *) ((void *) data_021c9df4), value));
    *ptr = value;
}

unsigned long func_0205db38(unsigned char *p)
{
    return func_0205db78((UnkStruct_0205db78 *) (((unsigned char *) data_021c9df4)), (unsigned char) (*p));
}
