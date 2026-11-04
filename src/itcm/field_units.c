/* field_units: 2 functions, module itcm
 * mwccarm 1.2/base -O4,s
 * func_01ffcb5c @ 0x01ffcb5c, 0x40 bytes, Thumb
 * func_01ffcb2c @ 0x01ffcb2c, 0x2e bytes, Thumb
 */

typedef struct {
    char pad_00[0x124];
    unsigned int width;
    unsigned int height;
} UnkStruct_01ffcb5c;

typedef struct {
    unsigned char *data;
} UnkStruct_01ffcb2c;

extern UnkStruct_01ffcb5c *data_020da1a8;

void *func_01ffcb5c(int x, int y)
{
    UnkStruct_01ffcb5c *s = data_020da1a8;
    void *p;

    if (x >= 0 && y >= 0 && x < s->width && y < s->height) {
        p = (char *) s + y * 48 + x * 8;
    } else {
        p = 0;
    }

    if (p != 0) {
        return p;
    } else {
        return 0;
    }
}

unsigned char func_01ffcb2c(int a, int b)
{
    UnkStruct_01ffcb2c *p;
    p = (UnkStruct_01ffcb2c *) func_01ffcb5c(a >> 4, b >> 4);
    if (p) {
        return p->data[(a & 0xf) + ((b & 0xf) << 4)];
    }
    return 0x15;
}
