/* func_020348fc @ 0x020348fc, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short unk_00;
    unsigned short f0 : 6;
    unsigned short b6 : 1;
    unsigned short b7 : 1;
    unsigned short b8 : 1;
} UnkStruct_020348fc;

extern char data_021ebcd4[];

extern int func_020b65c4(void);
extern void func_02034a48(unsigned short *p, int a, int b, int c, int d);
extern int func_020b67e8(int id);
extern void *func_02060f04(char *g, int id);
extern void func_020611bc(void *p, unsigned short *q, int a);
extern void func_02034a00(int id, unsigned short *q);
extern void func_02061194(void *p, unsigned short *q, int a);
extern void func_020349d0(int id, unsigned short *q);

void func_020348fc(UnkStruct_020348fc *self)
{
    int f8;
    unsigned short loc;
    unsigned char id;
    int b7;
    int b6;
    void *p;

    loc = self->unk_00;
    id = (unsigned char) self->f0;
    b7 = self->b7;
    if (self->b6) {
        b6 = 1;
    } else {
        b6 = 0;
    }
    if (self->b8) {
        f8 = 1;
    } else {
        f8 = 0;
    }
    if (self->f0 == func_020b65c4()) {
        func_02034a48(&loc, b7, b6, f8, 0);
        return;
    }
    if (func_020b67e8(id) != 0) {
        p = func_02060f04(data_021ebcd4, id);
        if (p == 0) {
            return;
        }
        if (b6 != 0) {
            func_020611bc(p, &loc, b7);
            func_02034a00(id, &loc);
        } else {
            func_02061194(p, &loc, b7);
            func_020349d0(id, &loc);
        }
    } else {
        if (b6 != 0) {
            func_02034a00(id, &loc);
        } else {
            func_020349d0(id, &loc);
        }
    }
}
