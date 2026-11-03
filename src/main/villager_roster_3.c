/* villager_roster_3: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207cf14 @ 0x0207cf14, 0x60 bytes, Thumb
 * func_0207cee4 @ 0x0207cee4, 0x30 bytes, Thumb
 * func_0207cec0 @ 0x0207cec0, 0x24 bytes, Thumb
 * func_0207ce98 @ 0x0207ce98, 0x28 bytes, Thumb
 * func_0207ce70 @ 0x0207ce70, 0x28 bytes, Thumb
 * func_0207ce48 @ 0x0207ce48, 0x28 bytes, Thumb
 */

typedef struct {
    unsigned short unk_00;
    unsigned char unk_02[12];
    unsigned char pad_0E;
    unsigned char unk_0F;
} UnkStruct_0207cf14;

typedef struct {
    unsigned char data[0x7ec];
} BigStruct;

struct Elem {
    char data[0x7ec];
};

extern int func_02003704(UnkStruct_0207cf14 *obj);
extern UnkStruct_0207cf14 *func_0208150c(BigStruct *p);
extern int memcmp(const void *s1, const void *s2, int n);
extern int func_0207cf74(int);

int func_0207cf14(BigStruct *base, UnkStruct_0207cf14 *obj)
{
    int result = -1;
    if (func_02003704(obj)) {
        int i;
        for (i = 0; i < 8; i++) {
            UnkStruct_0207cf14 *p = func_0208150c(&base[i]);
            if (obj->unk_00 == p->unk_00 && memcmp(&obj->unk_02, &p->unk_02, 12) == 0 && obj->unk_0F == p->unk_0F) {
                result = i;
                break;
            }
        }
    }
    return result;
}

int func_0207cee4(int arg0, int arg1)
{
    int result;
    result = 0;
    if (func_0207cf74(arg1) != 0) {
        result = func_02003704((UnkStruct_0207cf14 *) ((int) func_0208150c((BigStruct *) (arg0 + arg1 * 0x7ec))));
    }
    return result;
}

int func_0207cec0(int param1, int param2)
{
    int result;
    int temp;

    result = 0;
    temp = param2;

    if (func_0207cf74(temp) != 0) {
        result = param1 + (param2 * 0x7ec);
    }

    return result;
}

struct Elem *func_0207ce98(struct Elem *base, void *argument1)
{
    struct Elem *result = 0;
    int index = func_0207cf14((BigStruct *) ((void *) base), (UnkStruct_0207cf14 *) ((void *) argument1));
    if (func_0207cf74(index) != 0) {
        result = base + index;
    }
    return result;
}

int func_0207ce70(unsigned short *arr, int n)
{
    arr += n - 1;
    while (n > 0) {
        if (*arr != 0 && *arr != 0x3000) {
            return n;
        }
        n--;
        arr--;
    }
    return 0;
}

int func_0207ce48(unsigned short *r0, unsigned short *r1, int r2)
{
    int r5 = 0;
    int r4;
    int r3;
    int result;

    while (r5 < r2) {
        r4 = *r0;
        r3 = *r1;
        if (r4 != r3) {
            return 0;
        }
        r5++;
        r0 += 1;
        r1 += 1;
    }
    return 1;
}
