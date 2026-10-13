/* func_ov003_0221d64c @ 0x0221d64c, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_021e5a2c[];
extern void *func_0207cec0(void *p, int n);
extern void *func_02080b64(void *p);

struct UnkStruct_0221d64c {
    char pad_00[0x136];
    unsigned short code;
};

typedef struct {
    unsigned char b : 5;
} Low5;

unsigned char func_ov003_0221d64c(struct UnkStruct_0221d64c *obj)
{
    void *base;
    int flag;
    unsigned short val;
    int offset;
    void *tmp;

    base = data_021e5a2c;
    flag = 0;
    val = obj->code;
    if (val >= 0x5001 && val <= 0x5008) {
        flag = 1;
    }
    if (flag) {
        offset = val - 0x5001;
    } else {
        offset = -1;
    }
    tmp = func_0207cec0(base, offset);
    tmp = func_02080b64(tmp);
    return ((Low5 *) tmp)->b;
}
