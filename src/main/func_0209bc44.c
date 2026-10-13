/* func_0209bc44 @ 0x0209bc44, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa];
    unsigned char byte_at_0xa;
} UnkStruct_0209bc44;

extern int func_0209bc54(int, unsigned char, UnkStruct_0209bc44 *);

int func_0209bc44(UnkStruct_0209bc44 *a, int b)
{
    return func_0209bc54(b, a->byte_at_0xa, a);
}
