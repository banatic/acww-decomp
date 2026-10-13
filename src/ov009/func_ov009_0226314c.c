/* func_ov009_0226314c @ 0x0226314c, 0x68 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b2a68(void *buf, void *ptr);
extern int func_020b2a4c(void *buf);
extern void func_020b2a64(void *buf);

typedef struct {
    unsigned char pad_00[0x136];
    unsigned short unk_136;
} UnkStruct_0226314c;

typedef struct {
    char data[10];
} Elem;

extern Elem data_020d1f24[];

int func_ov009_0226314c(UnkStruct_0226314c *param)
{
    int local[4];
    int flag = 0;
    unsigned int value;
    unsigned int v;
    Elem *ptr;
    int ret;

    value = param->unk_136;
    if (value >= 0x5000 && value <= 0x5021) {
        flag = 1;
    }

    if (flag != 0) {
        v = value & 0xfff;
    } else {
        v = 0xffffffff;
    }

    if (v < 0x22) {
        ptr = &data_020d1f24[v];
    } else {
        ptr = data_020d1f24;
    }

    func_020b2a68(local, ptr);
    ret = func_020b2a4c(local);
    func_020b2a64(local);
    return ret;
}
