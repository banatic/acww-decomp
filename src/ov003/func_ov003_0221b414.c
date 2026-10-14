/* func_ov003_0221b414 @ 0x0221b414, 0x190 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z, w;
} UnkStruct_0221b414;

extern int data_020d1a10[4];
extern void *data_ov003_022383ac;
extern void *data_ov003_022383c8;

extern void func_0205556c(void *p, unsigned int tag, void *data);
extern int func_ov003_0221a8c4(void *self);
extern UnkStruct_0221b414 *func_020b03f8(void);
extern void func_0203efb0(void *self, unsigned short v);
extern void func_ov003_0221a004(void *self, int a);
extern void func_ov003_0221a7a0(void *self);
extern void func_02031288(void *a, void *b, void *c, int d, int e, void *f, int g);
extern void func_ov003_0221b064(void *self, int a, int b);
extern void func_0200451c(void *p);
extern void func_0203edd0(void *self);
extern void func_ov003_02236254(void *self);

void func_ov003_0221b414(char *self)
{
    int idx;
    int tmp;
    UnkStruct_0221b414 *arr;
    char *q;

    *(unsigned short *) (self + 0x39a) = 0xfff1;

    *(int *) (self + 0x2f8) = data_020d1a10[0];
    *(int *) (self + 0x2fc) = data_020d1a10[1];
    *(int *) (self + 0x300) = data_020d1a10[2];
    *(int *) (self + 0x304) = data_020d1a10[3];

    func_0205556c(self + 0x134, 0x534e5730, &data_ov003_022383ac);
    func_0205556c(self + 0x1d0, 0x534e5731, &data_ov003_022383c8);

    if (func_ov003_0221a8c4(self)) {
        idx = *(int *) (self + 8) & 1;
        arr = func_020b03f8();
        *(int *) (self + 0x26c) = arr[idx & 1].w;

        idx = *(int *) (self + 8) & 1;
        arr = func_020b03f8();
        arr[idx & 1].x = *(int *) (self + 0x5c);
        arr[idx & 1].y = *(int *) (self + 0x60);
        arr[idx & 1].z = *(int *) (self + 0x64);

        tmp = *(int *) (self + 0x26c);
        idx = *(int *) (self + 8) & 1;
        arr = func_020b03f8();
        arr[idx & 1].w = tmp;
    }

    func_0203efb0(self, (unsigned short) *(int *) (self + 8));
    func_ov003_0221a004(self, 0);
    func_ov003_0221a7a0(self);

    *(int *) (self + 0x68) = *(int *) (self + 0x5c);
    *(int *) (self + 0x6c) = *(int *) (self + 0x60);
    *(int *) (self + 0x70) = *(int *) (self + 0x64);
    q = self + 0x68;
    *(int *) (self + 0x31c) = *(int *) (self + 0x68);
    *(int *) (self + 0x320) = *(int *) (q + 4);
    *(int *) (self + 0x324) = *(int *) (q + 8);

    func_02031288(self + 0x274, self + 0x5c, q, 0, *(int *) (self + 0x270), self, 0xb);

    *(int *) (self + 0x68) = *(int *) (self + 0x5c);
    *(int *) (self + 0x6c) = *(int *) (self + 0x60);
    *(int *) (self + 0x70) = *(int *) (self + 0x64);
    q = self + 0x68;
    *(int *) (self + 0x31c) = *(int *) (self + 0x68);
    *(int *) (self + 0x320) = *(int *) (q + 4);
    *(int *) (self + 0x324) = *(int *) (q + 8);

    *(unsigned char *) (self + 0x369) = *(unsigned char *) (self + 0x284);

    func_ov003_0221b064(self, 0, 0);
    func_0200451c(self + 0x328);
    func_0203edd0(self);
    func_ov003_02236254(self);
}
