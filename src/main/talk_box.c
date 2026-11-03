/* talk_box: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02068cbc @ 0x02068cbc, 0x20 bytes, Thumb
 * func_02068c9c @ 0x02068c9c, 0x20 bytes, Thumb
 * func_02068c6c @ 0x02068c6c, 0x2e bytes, Thumb
 * func_02068c3c @ 0x02068c3c, 0x2e bytes, Thumb
 * func_02068c24 @ 0x02068c24, 0x16 bytes, Thumb
 * func_02068c10 @ 0x02068c10, 0x14 bytes, Thumb
 * func_02068be4 @ 0x02068be4, 0x2a bytes, Thumb
 * func_02068bd8 @ 0x02068bd8, 0xc bytes, Thumb
 * func_02068bc8 @ 0x02068bc8, 0xe bytes, Thumb
 */

typedef struct {
    char pad_00[0xC];
    char data[0x70];
    int unk_7C;
} UnkStruct_02068cbc;

struct UnkStruct_02068c3c {
    unsigned char pad_00[0x0c];
    unsigned char sub[0x70];
    unsigned int unk_7C;
};

typedef struct {
    char pad_00[0x50];
    char data[0x24];
    char *ptr1;
    char *ptr2;
    int counter;
} UnkStruct_02068be4;

extern int func_0208a234(void *);
extern int func_0208a20c(void *ptr);
extern void func_0208fdc0(void *ptr, int);
extern void func_0208fdb8(void *ptr);
extern void func_0208fbd8(char *a, char *b, char *c);
extern int func_0208fbf0(char *a);
extern int func_0208fbe0(void *);

int func_02068cbc(UnkStruct_02068cbc *p)
{
    if (p->unk_7C == 0) {
        if (func_0208a234(p->data) == 0) {
            return 1;
        }
    }
    return 0;
}

int func_02068c9c(void *p)
{
    return (*(int *) ((char *) p + 0x7c) == 0) && (func_0208a234((char *) p + 0xc) == 1);
}

int func_02068c6c(void *param)
{
    if (*(unsigned int *) ((char *) param + 0x7c) == 0) {
        if (func_0208a234((char *) param + 0xc) == 2) {
            param = (char *) param + 0xc;
            if (func_0208a20c(param)) {
                return 1;
            }
        }
    }
    return 0;
}

int func_02068c3c(struct UnkStruct_02068c3c *obj)
{
    if (obj->unk_7C != 0) {
        goto fail;
    }
    if (func_0208a234(&obj->sub) != 3) {
        goto fail;
    }
    if (func_0208a20c(&obj->sub) == 0) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}

void func_02068c24(void *ptr, int argument1)
{
    func_0208fdc0((char *) ptr + 0x50, (int) argument1);
    *(unsigned int *) ((char *) ptr + 0x7c) = 0xFFFFFFFF;
}

void func_02068c10(void *arg)
{
    void *r4 = arg;
    func_0208fdb8((char *) r4 + 0x50);
    *(unsigned int *) ((char *) r4 + 0x7c) = 4;
}

void func_02068be4(UnkStruct_02068be4 *p)
{
    func_0208fbd8(p->data, p->ptr1 + 0x59, p->ptr2 + 0x4b);
    func_0208fbf0(p->data);
    if (p->counter > 0) {
        p->counter--;
    }
}

int func_02068bd8(void *arg)
{
    return func_0208fbe0((char *) arg + 0x50);
}

unsigned char func_02068bc8(int x)
{
    if (x == 9) {
        x = 2;
    }
    x++;
    return (unsigned char) x;
}
