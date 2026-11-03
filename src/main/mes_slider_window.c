/* mes_slider_window: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020aba3c @ 0x020aba3c, 0x20 bytes, Thumb
 * func_020aba24 @ 0x020aba24, 0x18 bytes, Thumb
 * func_020aba08 @ 0x020aba08, 0x1a bytes, Thumb
 * func_020ab9ec @ 0x020ab9ec, 0x1a bytes, Thumb
 * func_020ab9c8 @ 0x020ab9c8, 0x24 bytes, Thumb
 * func_020ab9ac @ 0x020ab9ac, 0x1a bytes, Thumb
 * func_020ab994 @ 0x020ab994, 0x18 bytes, Thumb
 * func_020ab988 @ 0x020ab988, 0xc bytes, Thumb
 */

struct UnkStruct_020aba24 {
    char pad_00[0x6c];
    char unk_6C[0xd0];
    int unk_13C;
};

typedef struct {
    unsigned char pad_00[0x13c];
    int unk_13C;
    unsigned char pad_140[3];
    unsigned char unk_143;
} UnkStruct020ab994;

extern int func_0208e484(void *ptr);
extern void func_0200467c(int cmd);
extern void func_0208f0c4(void *, int);
extern int func_0208f098(char *);
extern void func_020abc6c(void *obj, int n);

void func_020aba24(struct UnkStruct_020aba24 *obj);
void func_020ab9c8(void *obj);
void func_020ab994(UnkStruct020ab994 *s);

void func_020aba3c(void *ptr)
{
    if (func_0208e484((char *) ptr + 0x20)) {
        func_0200467c(0x27);
        func_020aba24((struct UnkStruct_020aba24 *) ptr);
    }
}

void func_020aba24(struct UnkStruct_020aba24 *obj)
{
    obj->unk_13C = 8;
    func_0208f0c4(obj->unk_6C, 2);
}

void func_020aba08(char *r0)
{
    if (func_0208f098(r0 + 0x6c) != 0) {
        func_020ab994((UnkStruct020ab994 *) r0);
    }
}

void func_020ab9ec(void *ptr)
{
    if (func_0208f098((char *) ((char *) ptr + 0x6c)) != 0) {
        func_020ab9c8(ptr);
    }
}

void func_020ab9c8(void *obj)
{
    *(int *) ((char *) obj + 0x13c) = 10;
    func_020abc6c(obj, 9);
    obj = (char *) obj + 0x6c;
    func_0208f0c4(obj, 1);
}

void func_020ab9ac(void *ptr)
{
    if (func_0208e484((char *) ptr + 0x20)) {
        func_020ab994((UnkStruct020ab994 *) ptr);
    }
}

void func_020ab994(UnkStruct020ab994 *s)
{
    s->unk_13C = 11;
    s->unk_143 = 0;
}

void func_020ab988(unsigned char *r0)
{
    unsigned char r2 = 0;
    unsigned short r1 = 0x143;
    r0[r1] = r2;
}
