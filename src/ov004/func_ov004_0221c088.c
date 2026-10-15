/* func_ov004_0221c088 @ 0x0221c088, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_0206f9d8(int (*predicate)(unsigned short *, int));
extern int func_0206fa28(int, int);
extern int func_ov004_0221c844(void *, int);
extern int func_ov004_0221d468(void *arg0, int arg1);
#define TilePredicate_func_ov004_0221d468 ((int (*)(unsigned short *, int)) func_ov004_0221d468)

void func_ov004_0221c088(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) *(int *) (self + 0x8e0) + 0x4) == 0x5 &&
        func_0206fa28(func_0206f9d8(TilePredicate_func_ov004_0221d468), 0xd) != 0x0) {
        func_ov004_0221c844(self, 0xb);
        return;
    }
}

#undef TilePredicate_func_ov004_0221d468
