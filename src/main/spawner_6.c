/* spawner_6: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02084dc8 @ 0x02084dc8, 0x38 bytes, Thumb
 * func_02084dac @ 0x02084dac, 0x1c bytes, Thumb
 * func_02084d9c @ 0x02084d9c, 0x10 bytes, Thumb
 * func_02084d8c @ 0x02084d8c, 0xe bytes, Thumb
 * func_02084d84 @ 0x02084d84, 0x8 bytes, Thumb
 * func_02084d5c @ 0x02084d5c, 0x26 bytes, Thumb
 * func_02084d34 @ 0x02084d34, 0x26 bytes, Thumb
 */

typedef struct {
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned short d;
    unsigned char e;
    unsigned char unk_0F;
} UnkStruct_02084dc8;

struct UnkStruct_02084d8c {
    char pad_00[0x70];
    unsigned char flag;
    unsigned int data;
};

typedef struct {
    unsigned char pad_00[2];
    unsigned short id;
    unsigned char pad_04[16];
} UnkStruct_02084d5c;

typedef struct {
    unsigned short id;
    unsigned char pad_02[18];
} Entry;

extern const unsigned int data_021fbee8[3];
extern int data_020e1b8c;

void func_02084dc8(UnkStruct_02084dc8 *out, const unsigned short *p_u16, unsigned char b1, unsigned char b2,
                   const UnkStruct_02084dc8 *src)
{
    out->d = *p_u16;
    out->e = b1;
    out->unk_0F = b2;
    if (src) {
        out->a = src->a;
        out->b = src->b;
        out->c = src->c;
    } else {
        out->a = data_021fbee8[0];
        out->b = data_021fbee8[1];
        out->c = data_021fbee8[2];
    }
}

void func_02084dac(int param)
{
    func_02084dc8((UnkStruct_02084dc8 *) param, (const unsigned short *) (&data_020e1b8c), 0x33, 0, 0);
}

int func_02084d9c(int unused, unsigned char *data)
{
    int result = 0;
    unsigned char v = data[0xf];
    if (v > 0 && v < 5) {
        result = 1;
    }
    return result;
}

void func_02084d8c(struct UnkStruct_02084d8c *obj, unsigned int *src)
{
    unsigned char *p = (unsigned char *) obj;
    p += 0x70;
    *p = 1;
    obj->data = *src;
}

void func_02084d84(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (112))) + (0)) = 0;
}

UnkStruct_02084d5c *func_02084d5c(unsigned short *value, UnkStruct_02084d5c *array, int count)
{
    int i;
    UnkStruct_02084d5c *p;

    p = array;
    for (i = 0; i < count; i++) {
        if (p->id == *value) {
            return p;
        }
        p++;
    }
    return 0;
}

Entry *func_02084d34(Entry *key, Entry *list, int count)
{
    Entry *p;
    int i;

    p = list;
    i = 0;
    while (i < count) {
        if (key->id == p->id) {
            return p;
        }
        p++;
        i++;
    }
    return 0;
}
