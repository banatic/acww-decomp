/* slot_pool_3: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02083cb8 @ 0x02083cb8, 0x6 bytes, Thumb
 * func_02083cb4 @ 0x02083cb4, 0x2 bytes, Thumb
 * func_02083ca8 @ 0x02083ca8, 0xc bytes, Thumb
 * func_02083c9c @ 0x02083c9c, 0xc bytes, Thumb
 * func_02083c84 @ 0x02083c84, 0x18 bytes, Thumb
 * func_02083c78 @ 0x02083c78, 0xc bytes, Thumb
 */

typedef struct {
    unsigned char unk_00;
} UnkStruct_02083cb8;

struct UnkStruct_02083ca8 {
    unsigned int unk_00;
    unsigned int unk_04;
};

struct UnkStruct_02083c84 {
    char *unk_00;
};

extern char data_020e1b70;
extern void func_020edb3c(void *obj);

void func_02083cb8(UnkStruct_02083cb8 *p)
{
    p->unk_00 = 0;
}

void func_02083cb4(void *receiver) {}

void func_02083ca8(struct UnkStruct_02083ca8 *r0, unsigned int r1)
{
    r0->unk_00 = (unsigned int) &data_020e1b70;
    r0->unk_04 = r1;
}

void func_02083c9c(int **out)
{
    *out = ((int *) &data_020e1b70);
}

void *func_02083c84(struct UnkStruct_02083c84 *obj)
{
    obj->unk_00 = &data_020e1b70;
    func_020edb3c(obj);
    return obj;
}

void func_02083c78(void **out)
{
    *out = &data_020e1b70;
}
