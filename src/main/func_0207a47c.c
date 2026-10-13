/* func_0207a47c @ 0x0207a47c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cf14(void *, int);
extern int func_0207cf74(int);

typedef struct UnkStruct_0207a47c {
    char pad_00[0x4078];
    unsigned short b0 : 1;
    unsigned short flag : 1;
    unsigned short val : 3;
} UnkStruct_0207a47c;

int func_0207a47c(UnkStruct_0207a47c *s, int b)
{
    int v;

    if (s->flag != 0) {
        v = func_0207cf14(s, b);
        if (func_0207cf74(v) == 0) {
            goto ret0;
        }
        if (s->val != v) {
            goto ret0;
        }
        return 1;
    ret0:
        return 0;
    } else {
        return 0;
    }
}
