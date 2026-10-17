/* Exercise the actual copied functions, vector consumer and payload writer.
 * The expected offsets come from the ARM stack, not the host's local order. */
static int failed;
extern void *func_0201c2c8(void *, void *);
extern int func_ov003_02215f00(void *, const int *, int, int);

int func_02096614(unsigned char *flag, unsigned int *x, unsigned int *z, int a, void *b)
{
    (void) a;
    (void) b;
    *flag = 1;
    *x = 0x12300;
    *z = 0x45600;
    return 1;
}
short func_020e8ed8(int x, int z)
{
    if (x != 0x12300 || z != 0x45600) {
        failed = 1;
    }
    return 0x6789;
}
void *func_02096190(void *p)
{
    return p;
}
void *func_0201c314(void *a, void *b)
{
    (void) b;
    return a;
}

unsigned int func_0200e92c(void *p)
{
    int *words = p;
    words[0] = words[1] = words[2] = 0;
    return 0;
}
void func_0200e90c(void *p, int a, int b, int c)
{
    int *words = p;
    words[0] = a;
    words[1] = b;
    words[2] = c;
}
int func_0200e894(void *self, void *p)
{
    (void) self;
    int *words = p;
    if (words[0] != 0x4d || words[1] != 6 || words[2] != 9 || words[3] != 0x11100 || words[4] != 0x33300) {
        failed = 2;
    }
    return 7;
}
int func_0200e91c(void *p)
{
    (void) p;
    return 0;
}

int main(void)
{
    int self[32] = {0};
    int vector[3] = {0x11100, 0x22200, 0x33300};
    /* The actual consumer returns short. Native entry wrappers normally widen
     * it; this fixture links directly, so only its low 16 bits are defined. */
    if ((unsigned short) (unsigned int) func_0201c2c8(self, 0) != 0x6789) {
        return 3;
    }
    if (func_ov003_02215f00(self, vector, 6, 9) != 7) {
        return 4;
    }
    return failed;
}
