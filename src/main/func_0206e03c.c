/* func_0206e03c @ 0x0206e03c, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x74];
} UnkStruct_0206e03c;

typedef struct {
    unsigned char pad_00[0xe8];
    UnkStruct_0206e03c arr[4];
    unsigned char pad_2B8[0x308 - 0x2b8];
    int unk_308[5];
    int unk_31C;
} UnkStruct_0206e03c_2;

extern void func_0206df1c(UnkStruct_0206e03c_2 *s, unsigned short *p1, int *a, int *b);
extern void func_020a88ec(void *o);
extern void func_020a887c(void *o);
extern void func_020a8874(void *o, void *p, int n);
extern void func_0206db74(UnkStruct_0206e03c *e);
extern void func_0206dba8(UnkStruct_0206e03c *e, void *o, int m);
extern void func_0206dbc0(UnkStruct_0206e03c *e, void *o);
extern void *data_020df270;

void func_0206e03c(UnkStruct_0206e03c_2 *s, unsigned short *p1, int flag)
{
    unsigned char obj[0x60];
    unsigned short buf[42];
    int i;
    int len;
    UnkStruct_0206e03c *e;
    int zero;

    func_0206df1c(s, p1, s->unk_308, &s->unk_31C);
    func_020a88ec(obj);
    *(void **) obj = &data_020df270;
    buf[0] = 0;
    zero = 0;
    for (i = 0; i < 4; i++) {
        len = s->unk_308[i + 1] - s->unk_308[i];
        e = &s->arr[i];
        func_0206db74(e);
        if (len != 0) {
            func_020a8874(obj, p1 + s->unk_308[i], len);
            if (flag != 0) {
                int m;
                if (i == s->unk_31C) {
                    m = 1;
                } else {
                    m = zero;
                }
                func_0206dba8(e, obj, m);
            } else {
                func_0206dbc0(e, obj);
            }
        } else {
            if (flag != 0 && i == s->unk_31C) {
                func_020a8874(obj, buf, 1);
                func_0206dba8(e, obj, 1);
            } else {
                func_0206db74(e);
            }
        }
    }
    *(void **) obj = &data_020df270;
    func_020a887c(obj);
}
