/* func_020f87f0 @ 0x020f87f0, 0x28 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[14];
    unsigned short unk_0E;
} UnkStruct_020f87f0;

extern int func_020f7bc4(void *, int, void *);

int func_020f87f0(UnkStruct_020f87f0 *obj)
{

    func_020f7bc4(obj, 0x51f, ((char *) obj) + 4);

    obj->unk_0E = 0;

    return 0;
}
