/* order_catalog_cursor_4: 2 functions, module ov142
 * mwccarm 1.2/base -O4,s
 * func_ov142_0229af4c @ 0x0229af4c, 0x48 bytes, Thumb
 * func_ov142_0229af1c @ 0x0229af1c, 0x30 bytes, Thumb
 */

typedef struct {
    char pad_00[0x8d];
    unsigned char a;
    char pad_8E[44];
    unsigned char b;
    char pad_BB[45];
    char c[1];
} UnkStruct_0229af1c;

extern void func_ov002_0220a314(void *);
extern void func_ov002_0220a2b4(void *);
extern int func_ov142_0229b04c(void *);
extern int func_ov142_0229afb0(void *);
extern void func_ov002_0220a05c(char *ptr, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov142_0229af1c(UnkStruct_0229af1c *obj, int p1, int p2);

void func_ov142_0229af4c(void *p)
{
    unsigned char c;
    int a, b;

    c = *(unsigned char *) ((char *) p + 0xc0);
    if (c == 0x13 || (c >= 9 && c <= 0x11)) {
        func_ov002_0220a314((char *) p + 0xe8);
    } else {
        func_ov002_0220a2b4((char *) p + 0xe8);
    }
    a = func_ov142_0229b04c(p);
    b = func_ov142_0229afb0(p);
    func_ov142_0229af1c((UnkStruct_0229af1c *) p, a, b);
}

void func_ov142_0229af1c(UnkStruct_0229af1c *obj, int p1, int p2)
{
    func_ov002_0220a05c(obj->c, p1, p2, 3, 1);
    obj->b = obj->a;
    func_ov002_02208098((void *) (obj), 8);
}
