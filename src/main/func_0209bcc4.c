/* func_0209bcc4 @ 0x0209bcc4, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209bcd4(unsigned int, unsigned char);

typedef struct {
    unsigned char pad_00[10];
    unsigned char byte;
} UnkStruct_0209bcc4;

int func_0209bcc4(UnkStruct_0209bcc4 *a, unsigned int b)
{
    return func_0209bcd4(b, a->byte);
}
