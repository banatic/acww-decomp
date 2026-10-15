/* func_0204cfc8 @ 0x0204cfc8, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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

extern int data_021c80bc;
extern int data_021fbe94;
extern int func_020e9948(void *a, int b);
extern void func_0204ecf8(void *);
extern RecT *func_020b682c(void);
extern void func_0204d594(SelfT *self, int r6);
extern void func_0204d08c(SelfT *self, int r7, int f58);
extern void *func_0204d3f0(SelfT *self, int r7, int f58, int r6);
extern int func_0204ebb0(int a, void *r4, void *bufptr, int r6);
extern unsigned char data_020e54a8;
extern void func_0204d0ac(int a);
extern void func_020e993c(int r6, void *r4);

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
            func_0204d08c(self, r7, self->unk_58);

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
