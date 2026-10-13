/* func_0205fca0 @ 0x0205fca0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xc];
    int unk_0C;
} UnkStruct_0205fca0;

extern void func_0206026c(UnkStruct_0205fca0 *s, int arg);

void func_0205fca0(UnkStruct_0205fca0 *s)
{
    s->unk_0C += 0x1000;
    if (s->unk_0C >= 0x28000) {
        func_0206026c(s, 0);
    }
}
