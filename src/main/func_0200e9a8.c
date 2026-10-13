/* func_0200e9a8 @ 0x0200e9a8, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096614(void *p1, void *p2, void *p3, int p4, int p5);
extern int func_0209658c(void *p1, int p2, int p3);

struct UnkStruct_0200e9a8 {
    char pad_00[0x800];
    int value;
};

int func_0200e9a8(struct UnkStruct_0200e9a8 *a, char *b, int *c, int *d, short *e)
{
    int arg5;
    struct {
        unsigned char byte;
        short word;
        int word1;
        int word2;
    } local;
    int unused;

    arg5 = a->value;
    if (func_02096614(&local.byte, &local.word1, &local.word2, -1, arg5) == 0) {
        return 0;
    }
    if (func_0209658c(&local.word, -1, a->value) == 0) {
        return 0;
    }

    *b = local.byte;
    *c = local.word1;
    *d = local.word2;
    *e = local.word;
    return 1;
}
