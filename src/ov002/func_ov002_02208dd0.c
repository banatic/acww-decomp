/* func_ov002_02208dd0 @ 0x02208dd0, 0x28 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02209b94(void *, int);

void func_ov002_02208dd0(char *self)
{
    // DECLS
    int i;
    // ENDDECLS
    for (i = 0; i < 0x5; i++) {
        func_ov002_02209b94(self + 0x28 + (0x74 * i), -0x1);
    }
}
