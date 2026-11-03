/* scene_map: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204d08c @ 0x0204d08c, 0x20 bytes, Thumb
 * func_0204cfc8 @ 0x0204cfc8, 0xc4 bytes, Thumb
 * func_0204cfa4 @ 0x0204cfa4, 0x24 bytes, Thumb
 * func_0204cf64 @ 0x0204cf64, 0x40 bytes, Thumb
 * func_0204cf60 @ 0x0204cf60, 0x4 bytes, Thumb
 * func_0204cf5c @ 0x0204cf5c, 0x4 bytes, Thumb
 * func_0204cf34 @ 0x0204cf34, 0x28 bytes, Thumb
 * func_0204cf14 @ 0x0204cf14, 0x20 bytes, Thumb
 */

typedef struct {
    int unk_00;
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned short unk_06;
} RecT;

typedef struct {
    unsigned char pad_00[0x50];
    unsigned short unk_50;
    unsigned char pad_52[2];
    int unk_54;
    int unk_58;
} SelfT;

typedef struct {
    volatile unsigned int unk_00;
} UnkStruct_0204cf34;

extern int func_020b67ac(void);
extern unsigned short func_02060d7c(void *addr);
extern unsigned char data_021ebcd4[];
extern int data_021c80bc;
extern int data_021fbe94;
extern int func_020e9948(void *a, int b);
extern void func_0204ecf8(void *);
extern RecT *func_020b682c(void);
extern void func_0204d594(SelfT *self, int r6);
extern void *func_0204d3f0(SelfT *self, int r7, int f58, int r6);
extern int func_0204ebb0(int a, void *r4, void *bufptr, int r6);
extern unsigned char data_020e54a8;
extern void func_0204d0ac(int a);
extern void func_020e993c(int r6, void *r4);
extern void func_0205bdb0(void);
void func_0204d544(int a, int b);
void func_0204ecd4(void *a, int b);
extern void func_020ee62c(void *ptr);
extern void func_020edf54(void *ptr);
extern unsigned char data_020da13c[];
extern unsigned char data_020db898[];

void func_0204d08c(void *self, int *out, int count)
{
    if (func_020b67ac()) {
        *out = func_02060d7c((void *) data_021ebcd4);
    }
}

int func_0204cfc8(SelfT *self, void *arg1)
{
    int r6;
    int r7;
    RecT *rec;
    void *r4;
    int buf[2];

    self->unk_54 = 0;
    self->unk_58 = 0;

    if (data_021c80bc == 0) {
        int r = func_020e9948(arg1, 0x20);
        data_021c80bc = r;
        if (r != 0) {
            func_0204ecf8((void *) r);
        }
    }

    if (data_021c80bc != 0) {
        rec = func_020b682c();
        r6 = data_021fbe94;
        r7 = 0;
        buf[0] = 0;
        buf[1] = 0;

        if (rec != 0) {
            unsigned char v5 = rec->unk_05;
            unsigned char v4 = rec->unk_04;
            buf[0] = v4;
            buf[1] = v5;
            self->unk_58 = v4 * v5;

            func_0204d594(self, r6);

            r7 = rec->unk_00;
            func_0204d08c(self, (int *) r7, self->unk_58);

            self->unk_50 = rec->unk_06;
        }

        r4 = func_0204d3f0(self, r7, self->unk_58, r6);

        if (r4 != 0) {
            unsigned int flag;

            func_0204ebb0(data_021c80bc, r4, &buf[0], r6);

            flag = (data_020e54a8 != 0) ? 0 : 1;
            if (flag > 0) {
                func_0204d0ac(data_021c80bc);
            }

            func_020e993c(r6, r4);
        }
    }

    return 1;
}

int func_0204cfa4(int arg)
{
    if (func_0204cfc8((SelfT *) arg, (void *) data_021fbe94) == 0) {
        return 0;
    }
    func_0205bdb0();
    return 1;
}

int func_0204cf64(int param)
{
    int v = data_021fbe94;
    if ((*(void * *) &data_021c80bc)) {
        func_0204d544(param, v);
        func_0204ecd4((*(void * *) &data_021c80bc), v);
        func_020e993c(v, (*(void * *) &data_021c80bc));
        (*(void * *) &data_021c80bc) = 0;
    }
    return 1;
}

int func_0204cf60(void)
{
    return 1;
}

int func_0204cf5c(void)
{
    return 1;
}

void *func_0204cf34(void *ptr)
{
    UnkStruct_0204cf34 *s = (UnkStruct_0204cf34 *) ptr;
    s->unk_00 = (unsigned int) data_020db898;
    s->unk_00 = (unsigned int) data_020da13c;
    func_020ee62c(ptr);
    func_020edf54(ptr);
    return ptr;
}

void *func_0204cf14(void *p)
{
    *(int *) p = (int) ((char *) data_020db898);
    *(int *) p = (int) ((char *) data_020da13c);
    func_020ee62c(p);
    return p;
}
