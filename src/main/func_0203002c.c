/* func_0203002c @ 0x0203002c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
    int z;
} UnkStruct_0203002c;
typedef struct {
    unsigned char pad_00[0xc];
    UnkStruct_0203002c unk_0C;
} UnkStruct_0203002c_2;
extern void func_020eaca0(UnkStruct_0203002c *out, UnkStruct_0203002c *in, UnkStruct_0203002c_2 *a);
extern void func_020ea838(UnkStruct_0203002c *v);
void func_0203002c(UnkStruct_0203002c_2 *a, UnkStruct_0203002c *out)
{
    UnkStruct_0203002c t;
    func_020eaca0(&t, &a->unk_0C, a);
    out->x = t.x;
    out->y = t.y;
    out->z = t.z;
    func_020ea838(out);
}
