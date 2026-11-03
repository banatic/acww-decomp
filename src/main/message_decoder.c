/* message_decoder: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b4dc8 @ 0x020b4dc8, 0x40 bytes, Thumb
 * func_020b4dc0 @ 0x020b4dc0, 0x8 bytes, Thumb
 * func_020b4d70 @ 0x020b4d70, 0x50 bytes, Thumb
 * func_020b4d60 @ 0x020b4d60, 0xe bytes, Thumb
 * func_020b4d0c @ 0x020b4d0c, 0x54 bytes, Thumb
 * func_020b4cd8 @ 0x020b4cd8, 0x34 bytes, Thumb
 */

struct UnkStruct_020b4dc8 {
    int pad_00;
    int value;
    unsigned char x;
    unsigned char y;
};

struct UnkStruct_020b4dc8_2 {
    char pad_00[0x24];
    struct UnkStruct_020b4dc8 *data;
};

struct UnkStruct_020b4d0c {
    char pad_00[0x24];
    int unk_24;
};

struct UnkStruct_020b4d0c_2 {
    int arr[15];
};

typedef struct {
    char pad_00[0x24];
    void *unk_24;
} func_020b4cd8_param;

extern int func_020a86e4(void *p, unsigned char *b0, unsigned char *b1, unsigned char *b2);
extern int func_020a7c98(int, int);
extern struct UnkStruct_020b4d0c_2 data_020e5294;
extern int strcmp(int a, void *b);

void func_020b4dc8(struct UnkStruct_020b4dc8_2 *p)
{
    unsigned char b[3];
    struct UnkStruct_020b4dc8 *dst;
    unsigned int v;

    func_020a86e4((char *) p + 0x28, &b[0], &b[1], &b[2]);
    dst = (struct UnkStruct_020b4dc8 *) ((char *) p->data + 0xaf0);
    v = b[0];
    if (v < 3) {
        // nothing
    } else {
        v = -1;
    }
    dst->value = (int) v;
    dst->x = b[1];
    dst->y = b[2];
}

void func_020b4dc0(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (72))) + (0)) = 1;
}

int func_020b4d70(int r0)
{
    int r2;
    int r1;

    r2 = 1;
    if (r0 == 0) {
        r2 = 0;
    }
    r1 = 0x0000ff10;
    if (r0 >= r1) {
        r1 = 0x0000ff19;
        if (r0 <= r1) {
            r2 = 0;
        }
    }
    r1 = 0x0000ff21;
    if (r0 >= r1) {
        r1 = 0x0000ff3a;
        if (r0 <= r1) {
            r2 = 0;
        }
    }
    r1 = 0x0000ff41;
    if (r0 >= r1) {
        r1 = 0x0000ff5a;
        if (r0 <= r1) {
            r2 = 0;
        }
    }
    return r2;
}

int func_020b4d60(int *param1, int param2)
{
    int result;
    int *ptr;

    result = 1;
    ptr = (int *) ((char *) param1 + 0x3c);
    if (*ptr == param2) {
        result = 0;
    }
    return result;
}

int func_020b4d0c(struct UnkStruct_020b4d0c *param)
{
    struct UnkStruct_020b4d0c_2 local;
    int i;
    int result = 1;
    int value;

    local = data_020e5294;
    value = func_020a7c98(param->unk_24 + 0xafc, 0);
    for (i = 0; i < 15; i++) {
        if (local.arr[i] == value) {
            result = 0;
            break;
        }
    }
    return result;
}

int func_020b4cd8(func_020b4cd8_param *param)
{
    void *q = *(void **) ((char *) param->unk_24 + 0x18f0);
    int r = (*(int (**)(void *))((char *) *(void **) q + 0xc))(q);
    return strcmp(r, (char *) param->unk_24 + 0xafc) != 0;
}
