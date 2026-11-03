/* field_actor_looks: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02010134 @ 0x02010134, 0x2c bytes, Thumb
 * func_020100e8 @ 0x020100e8, 0x4c bytes, Thumb
 * func_020100d0 @ 0x020100d0, 0x16 bytes, Thumb
 * func_020100b8 @ 0x020100b8, 0x16 bytes, Thumb
 */

struct UnkStruct_02010134 {
    char pad_00[0x428];
    char unk_428[1];
    char pad_429[0x86B];
    int unk_C94;
};

extern int func_0205e1bc(void *ptr);
extern void func_0206439c(int a, int b, int c, int d);
extern void func_0206435c(int, int, int, int);

void func_02010134(struct UnkStruct_02010134 *unk)
{
    if (unk->unk_C94 == 1) {
        if (func_0205e1bc(unk->unk_428)) {
            unk->unk_C94 = 2;
        }
    }
}

int func_020100e8(void *base, unsigned short *src, unsigned char a, unsigned char b, unsigned char c)
{
    if (*(int *) ((char *) base + 0xc94) == 2) {
        *(int *) ((char *) base + 0xc94) = 0;
        *(unsigned short *) ((char *) base + 0xc98) = *src;
        *(unsigned char *) ((char *) base + 0xc9a) = a;
        *(unsigned char *) ((char *) base + 0xc9b) = b;
        *(unsigned char *) ((char *) base + 0xc9c) = c;
        return 1;
    } else {
        return 0;
    }
}

void func_020100d0(int unused, int a, int b, int c, int d)
{
    func_0206439c(a, b, c, d);
}

void func_020100b8(int a, int b, int c, int d, int e)
{
    func_0206435c(b, c, d, e);
}
