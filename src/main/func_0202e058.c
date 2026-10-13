/* func_0202e058 @ 0x0202e058, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x28];
    unsigned short unk_28;
    char pad_2A[0x2];
    unsigned int unk_2C;
} UnkStruct_0202e058;

extern int func_0208308c(void *);
extern int func_0202df18(UnkStruct_0202e058 *, int, int);

int func_0202e058(UnkStruct_0202e058 *a, int b, int c)
{
    a->unk_28 = 0xFFFF;
    if (func_0208308c(&a->unk_2C) == 0) {
        return 0;
    }
    if (func_0202df18(a, b, c) == 0) {
        return 0;
    }
    return 1;
}
