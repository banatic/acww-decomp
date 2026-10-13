/* func_0209e49c @ 0x0209e49c, 0x118 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0209e49c {
    int w[4];
};

struct UnkStruct_0209e49c_2 {
    int w[3];
};

struct UnkStruct_0209e49c_3 {
    struct UnkStruct_0209e49c s16;
    struct UnkStruct_0209e49c_2 s12;
};

extern void func_0209e5b4(struct UnkStruct_0209e49c *a, struct UnkStruct_0209e49c_2 *b);
extern void func_0209e0c0(void *buf, int v);
extern void func_0209e234(void *buf, int v);
extern void func_0209e080(void *buf, int v);
extern void func_0209e200(void *buf, int v);
extern int func_0209de88(int a, int b, int c);

extern char data_021f3b28[];
extern char data_021f3b68[];

void func_0209e49c(struct UnkStruct_0209e49c_3 *out)
{
    unsigned char buf[8];
    struct UnkStruct_0209e49c local_s16;
    struct UnkStruct_0209e49c_2 local_s12;
    struct UnkStruct_0209e49c copy_s16;
    struct UnkStruct_0209e49c_2 copy_s12;
    struct UnkStruct_0209e49c copy2_s16;
    struct UnkStruct_0209e49c_2 copy2_s12;
    int v1;
    short v5;

    func_0209e5b4(&local_s16, &local_s12);
    copy_s16 = local_s16;
    out->s16.w[0] = copy_s16.w[0];
    out->s16.w[1] = copy_s16.w[1];
    out->s16.w[2] = copy_s16.w[2];
    out->s16.w[3] = copy_s16.w[3];

    copy_s12 = local_s12;
    out->s12.w[0] = copy_s12.w[0];
    out->s12.w[1] = copy_s12.w[1];
    out->s12.w[2] = copy_s12.w[2];

    v1 = *(int *) (data_021f3b28 + 0x4c);
    v5 = *(short *) (data_021f3b68 + 0x10);

    *(int *) &buf[0] = 0;
    *(int *) &buf[4] = 0;
    *(int *) &buf[0] = 0;
    *(int *) &buf[4] = 0;

    buf[5] = local_s16.w[0];
    buf[4] = local_s16.w[1];
    buf[3] = local_s16.w[2];
    buf[2] = local_s12.w[0];
    buf[1] = local_s12.w[1];
    buf[0] = local_s12.w[2];

    if (v1 < 0) {
        if (v1 < 0) {
            v1 = -v1;
        }
        func_0209e0c0(buf, v1);
    } else {
        func_0209e234(buf, v1);
    }

    if (v5 < 0) {
        if (v5 < 0) {
            v5 = -v5;
        }
        func_0209e080(buf, v5);
    } else {
        func_0209e200(buf, v5);
    }

    local_s16.w[0] = buf[5];
    local_s16.w[1] = buf[4];
    local_s16.w[2] = buf[3];
    local_s12.w[0] = buf[2];
    local_s12.w[1] = buf[1];
    local_s12.w[2] = buf[0];

    local_s16.w[3] =
        func_0209de88((unsigned char) local_s16.w[0], (unsigned char) local_s16.w[1], (unsigned char) local_s16.w[2]);

    copy2_s16 = local_s16;
    out->s16.w[0] = copy2_s16.w[0];
    out->s16.w[1] = copy2_s16.w[1];
    out->s16.w[2] = copy2_s16.w[2];
    out->s16.w[3] = copy2_s16.w[3];

    copy2_s12 = local_s12;
    out->s12.w[0] = copy2_s12.w[0];
    out->s12.w[1] = copy2_s12.w[1];
    out->s12.w[2] = copy2_s12.w[2];
}
