/* func_020a8630 @ 0x020a8630, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a87c8(int a, int b);

typedef struct {
    char pad_00[0xc];
    int val;
} UnkStruct_020a8630;

void func_020a8630(UnkStruct_020a8630 *s, unsigned char *dest, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        dest[i] = func_020a87c8(s->val, i);
    }
}
