/* func_020f2bf0 @ 0x020f2bf0, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_020f2bf0;

extern void func_020f45c4(void *p);
extern int data_0213edac;

UnkStruct_020f2bf0 *func_020f2bf0(UnkStruct_020f2bf0 *p)
{
    func_020f45c4(p);
    p->ptr = &data_0213edac;
    p->byte = 0x2d;
    return p;
}
