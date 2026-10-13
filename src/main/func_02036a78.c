/* func_02036a78 @ 0x02036a78, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035684(int a, int b, int c);

typedef struct {
    unsigned char pad_00[0x12];
    unsigned char flag;
} UnkStruct_02036a78;

void func_02036a78(UnkStruct_02036a78 *s, int b)
{
    if (s->flag == 0) {
        func_02035684(30, b, 0);
        s->flag = 1;
    }
}
