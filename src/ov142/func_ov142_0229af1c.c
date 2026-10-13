/* func_ov142_0229af1c @ 0x0229af1c, 0x30 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a05c(char *ptr, int a, int b, int c, int d);
extern void func_ov002_02208098(void *obj, int x);

typedef struct {
    char pad_00[0x8d];
    unsigned char a;
    char pad_8E[44];
    unsigned char b;
    char pad_BB[45];
    char c[1];
} UnkStruct_0229af1c;

void func_ov142_0229af1c(UnkStruct_0229af1c *obj, int p1, int p2)
{
    func_ov002_0220a05c(obj->c, p1, p2, 3, 1);
    obj->b = obj->a;
    func_ov002_02208098(obj, 8);
}
