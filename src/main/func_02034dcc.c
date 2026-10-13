/* func_02034dcc @ 0x02034dcc, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203735c(void *);
extern int func_020b6840(int);
extern int func_020b6660(int);
extern int func_020b22b8(int);
extern void *func_0203734c(void *);
extern void func_0206e9bc(void *);

typedef struct {
    char pad_00[0x24c];
    char unk_24C;
    char pad_24D[0x2f4 - 0x24c - 1];
    unsigned char unk_2F4;
} UnkStruct_02034dcc;

void func_02034dcc(UnkStruct_02034dcc *s)
{
    if (func_0203735c(&s->unk_24C) != 0) {
        int r4 = 1;
        int a = func_020b6840(1);
        int b;
        if (a == 0) {
            r4 = 0;
        }
        b = func_020b6660(a);
        if (b != 0 && func_020b22b8(b) != 0) {
            r4 = 0;
        }
        if (s->unk_2F4 != 0) {
            r4 = 0;
        }
        if (r4 != 0) {
            func_0206e9bc(func_0203734c(&s->unk_24C));
        }
    }
}
