/* func_ov003_0220f684 @ 0x0220f684, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *);
extern int func_02056f28(void *, int);
extern void func_ov003_02224384(unsigned int, unsigned int *, int);
extern void func_0200f268(void *, int);
extern void func_0200f27c(void *, int);

void func_ov003_0220f684(void *obj)
{
    unsigned int local[2];
    unsigned int a, b;
    struct UnkStruct_0220f684 {
        char pad[4];
        unsigned int a;
        unsigned int b;
    } *s;

    func_02010f5c(obj);
    if (func_02056f28((char *) obj + 0x2d0, 5) == 0) {
        return;
    }

    s = (struct UnkStruct_0220f684 *) ((char *) obj + 0x7d4);
    b = s->b;
    a = s->a;
    local[0] = a;
    local[1] = b;

    func_ov003_02224384(*(unsigned int *) ((char *) obj + 0x800), local, 3);
    func_0200f268(obj, 0x12);
    func_0200f27c(obj, 9);
}
