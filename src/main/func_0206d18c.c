/* func_0206d18c @ 0x0206d18c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x34];
    char unk_34;
} UnkStruct_0206d18c;

extern void *func_020a83ec(void *p);
extern void func_020a93e8(void *a, void *b);

void func_0206d18c(UnkStruct_0206d18c *obj)
{
    func_020a93e8(obj, func_020a83ec(&obj->unk_34));
}
