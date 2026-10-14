/* func_ov071_02278f44 @ 0x02278f44, 0x3c bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a;
    unsigned int b;
} Pair;

typedef struct {
    unsigned char pad_00[0xBC];
    Pair p1;
    Pair p2;
} UnkStruct_02278f44;

extern Pair __ptmf_null;
extern void func_0201612c(void *);

void func_ov071_02278f44(UnkStruct_02278f44 *self)
{
    func_0201612c(self);
    {
        Pair v = __ptmf_null;
        self->p1 = v;
        self->p2 = v;
    }
}
