/* func_ov003_02222d8c @ 0x02222d8c, 0x96 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y;
} UnkStruct_02222d8c;

extern int func_0204b910(void *);
extern void func_ov003_02222f8c(void *, void *, UnkStruct_02222d8c *);
extern int func_02044540(void);
extern void func_ov003_02222f0c(void *, UnkStruct_02222d8c *);
extern void func_ov003_02222e24(void *, void *, UnkStruct_02222d8c *);

void func_ov003_02222d8c(unsigned short *a, void *b, UnkStruct_02222d8c *c)
{
    UnkStruct_02222d8c p1, p2, p3;
    int in;
    unsigned short id;

    in = 0;
    id = *a;
    if (id >= 0x2f && id <= 0x56) {
        in = 1;
    }
    if (in != 0 || (id >= 0xc8 && id <= 0xcf) || (id >= 0x57 && id <= 0x5b)) {
        if (func_0204b910(a) == 0) {
            return;
        }
        p1.x = c->x;
        p1.y = c->y;
        func_ov003_02222f8c(a, b, &p1);
        return;
    }
    if (id == 0x67 || id == 0x6b) {
        if (func_02044540() == 0) {
            return;
        }
        p2.x = c->x;
        p2.y = c->y;
        func_ov003_02222f0c(b, &p2);
        return;
    }
    if ((id >= 0x66 && id <= 0x68) || (id >= 0x6a && id <= 0x6c)) {
        p3.x = c->x;
        p3.y = c->y;
        func_ov003_02222e24(a, b, &p3);
    }
}
