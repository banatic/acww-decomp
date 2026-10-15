/* func_0208725c @ 0x0208725c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0209529c(void *ptr);

typedef struct {
    char pad_00[0x1e];
    unsigned short unk_1E;
} UnkStruct_0208725c;

UnkStruct_0208725c *func_0208725c(UnkStruct_0208725c *arg)
{
    func_0209529c(arg);
    arg->unk_1E = 0xfff1;
    return arg;
}
