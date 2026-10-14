/* func_0209df7c @ 0x0209df7c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int pad_00;
    int a;
    int b;
    int c;
    int d;
} UnkStruct_0209df7c;

extern UnkStruct_0209df7c data_021dc744;

void func_0209df7c(unsigned char *dst)
{
    dst[0] = data_021dc744.c;
    dst[1] = data_021dc744.d;
    dst[2] = data_021dc744.b;
    dst[3] = data_021dc744.a;
}
