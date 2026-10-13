/* func_0209f47c @ 0x0209f47c, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f43e8;
extern int func_0206837c(void *);
extern void func_020ab670(int, int, int);
extern void func_020ab628(int, int, unsigned char *, int, unsigned char *, int, int);
extern void func_020ab5f8(int);
extern void func_02068388(void *, int);

typedef struct {
    unsigned char pad_00[0x1e];
    unsigned char flag;
    unsigned char pad_1F[0x40 - 0x1f];
    void *data;
} UnkStruct_0209f47c;

void func_0209f47c(UnkStruct_0209f47c *obj)
{
    unsigned char local[4];
    void *ptr;
    int result;

    if (obj->flag != 0) {
        return;
    }

    ptr = obj->data;
    result = func_0206837c(ptr);
    func_020ab670(result, 2, 1);

    local[0] = 0xc;
    local[1] = data_021f43e8;
    func_020ab628(result, 0, local, 1, &local[1], 0, 2);

    local[2] = 0xd;
    local[3] = data_021f43e8;
    func_020ab628(result, 1, &local[2], 1, &local[3], 0, 0);

    func_020ab5f8(result);
    func_02068388(ptr, 1);
}
