/* func_0208674c @ 0x0208674c, 0x6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short f;
} UnkStruct_0208674c;
typedef struct {
    unsigned char pad_00[0x3e];
    unsigned short f;
} UnkStruct_0208674c_2;
void func_0208674c(UnkStruct_0208674c *dst, UnkStruct_0208674c_2 *src)
{
    dst->f = src->f;
}
