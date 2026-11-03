/* talk_tags_15: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206b980 @ 0x0206b980, 0x2 bytes, Thumb
 * func_0206b97c @ 0x0206b97c, 0x2 bytes, Thumb
 * func_0206b964 @ 0x0206b964, 0x18 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x24];
    void *unk_24;
} UnkStruct_0206b964;

extern void func_0206844c(void *, void *, int);
extern void func_02068428(void *);

void func_0206b980(void) {}

void func_0206b97c(void *self, void *part) {}

void func_0206b964(UnkStruct_0206b964 *s, void *param2)
{
    func_0206844c(s->unk_24, param2, 0);
    func_02068428(s->unk_24);
}
