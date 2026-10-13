/* func_ov068_0226840c @ 0x0226840c, 0x98 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0226840c {
    int a;
    int b;
    int c;
} UnkStruct_0226840c;

typedef struct StructR6 {
    char pad_00[0x1c];
    unsigned char unk_1C;
} StructR6;

typedef struct StructR5 {
    char pad_00[0x5c];
    UnkStruct_0226840c sub;
    char pad_68[0x188 - 0x68];
    int unk_188;
    char pad_18C[0x19c - 0x18c];
    unsigned char unk_19C;
    char pad_19D[0x334 - 0x19d];
    int unk_334;
} StructR5;

extern int func_020164a0(void *addr, int value);
extern void func_0204f7e0(void *dst, void *src);
extern void func_ov068_022684a4(void *ptr, int a, int b, int c, int d);
extern int func_02056f94(void *addr);
extern void func_ov068_0226831c(StructR6 *r6, StructR5 *r5);

void func_ov068_0226840c(StructR6 *r6, StructR5 *r5)
{
    UnkStruct_0226840c local;
    if (func_020164a0(&r5->unk_334, 0) == 0x127) {
        UnkStruct_0226840c *p = &r5->sub;
        func_0204f7e0(&local, p);
        func_ov068_022684a4(p, local.a, 0xe66, 0x1ec, 0x31);
        func_ov068_022684a4(&p->c, local.c, 0xe66, 0x1ec, 0x31);
        r5->unk_19C = 1;
        if (r5->sub.a == local.a && p->c == local.c) {
            if (func_02056f94(&r5->unk_188) != 0) {
                func_ov068_0226831c(r6, r5);
            } else {
                r6->unk_1C = 1;
            }
        }
    }
}
