/* Exercise the actual copied functions, vector consumer and payload writer.
 * The expected offsets come from the ARM stack, not the host's local order. */
static int failed;
extern void *func_0201c2c8(void *, void *);
extern int func_ov003_02215f00(void *, const int *, int, int);
extern int func_ov003_02211d4c(void *, int, const int *, int, short);
extern int func_ov003_022118f8(void *, const int *, int, int, int, short);
extern int func_ov003_02211980(void *, const int *, int, int, short);
int data_020ccf94;
static int local_actor;
static int expected_state = 0x4d, expected_arg = 9, expected_item;

int func_02073908(int session, int player)
{
    (void) session;
    (void) player;
    return local_actor;
}

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
    unsigned char *bytes = p;
    if (words[0] != expected_state || words[1] != 6 || words[2] != expected_arg) {
        failed = 2;
    }
    if (expected_state == 0x4d) {
        if (words[3] != 0x11100 || words[4] != 0x33300) {
            failed = 2;
        }
    } else if (expected_state == 0x5e) {
        if (bytes[12] != 0x57 || words[4] != 0x11100 || words[5] != 0x22200 || words[6] != 0x33300) {
            failed = 5;
        }
    } else if (expected_state == 0x5f) {
        if (words[3] != 0x11100 || words[4] != 0x22200 || words[5] != 0x33300 ||
            *(unsigned short *) (bytes + 24) != expected_item || bytes[26] != 0x57) {
            failed = 6;
        }
    } else {
        failed = 7;
    }
    return 7;
}
int func_0200e91c(void *p)
{
    (void) p;
    return 0;
}

/* func_020a967c: func_02064658 fills eight bytes at the first local's address; the second word
 * is read through the second local (ROM 020a96a8 and 020a96d6: sp and sp+4). */
extern int func_020a967c(void *);
unsigned short data_021f4458[8];
int data_021f4428[2];
void func_02064658(void *a, int *b, int c, int d)
{
    (void) a;
    (void) d;
    if (c != 8) {
        failed = 12;
    }
    b[0] = 0x111;
    b[1] = 0x333;
}
int func_020a9ae4(int *a)
{
    return *a;
}

/* func_0201354c: func_020137ec reads a two-word point at the first local's address, the second
 * word being the second local (ROM 0201357a/0201357c and 02013614: sp+0x2c and sp+0x30). */
extern int func_0201354c(void *, unsigned int *, int *);
static unsigned int object_0201354c[5];
unsigned int *data_021c80bc = object_0201354c;
unsigned int data_021c172c[2], data_021c173c[2], data_021c1734[2], data_021c1744[2];
void func_0204f818(unsigned int *a, unsigned int *b, int *p)
{
    (void) p;
    *a = 0x12345;
    *b = 0x6789a;
}
int func_0204ed30(void *o, int *p)
{
    (void) o;
    (void) p;
    return 0;
}
int func_0204f658(void *o, int a, int b)
{
    (void) o;
    (void) a;
    (void) b;
    return 0;
}
int func_020137ec(void *p0, int *arr, unsigned int *point, void *step, int n, void *lim, int f, void *o)
{
    (void) p0;
    (void) arr;
    (void) step;
    (void) n;
    (void) lim;
    (void) f;
    (void) o;
    if (point[0] != 0x12345 || point[1] != 0x6789a) {
        failed = 13;
    }
    return 0;
}
int func_020ea990(int *a, int *b)
{
    (void) a;
    (void) b;
    return 0;
}
unsigned int func_02013738(void *p0, int *out, void *o)
{
    (void) p0;
    (void) out;
    (void) o;
    return 9;
}

static int check_point_layouts(void)
{
    unsigned char self[0xa4] = {0};
    self[0x8d] = 2;
    if (func_020a967c(self) != 1 || *(int *) (self + 0x9c) != 0x111 || *(int *) (self + 0xa0) != 0x222 ||
        *(int *) (self + 0x90) != 0x111) {
        return 14;
    }
    unsigned int p1[2] = {0, 0};
    int p2[3] = {0x1000, 0x2000, 0x3000};
    if (func_0201354c(self, p1, p2) != 4 || p1[0] != 0x12345 || p1[1] != 0x6789a) {
        return 15;
    }
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
    int actor[0x824 / 4] = {0};
    unsigned short *items = (unsigned short *) ((char *) actor + 0x820);
    expected_state = 0x5e;
    expected_arg = -9;
    if (func_ov003_02211d4c(actor, 0x57, vector, 6, -9) != 7) {
        return 8;
    }
    expected_state = 0x5f;
    expected_item = 0xa123;
    if (func_ov003_022118f8(actor, vector, expected_item, 0x57, 6, -9) != 7 || items[0] != 0xfff1 || items[1] != 0xfff1) {
        return 9;
    }
    local_actor = 1;
    items[0] = 0x1234;
    items[1] = 0x5678;
    if (func_ov003_022118f8(actor, vector, expected_item, 0x57, 6, -9) != 7 || items[0] != 0x1234 || items[1] != 0x5678) {
        return 10;
    }
    expected_item = 0xfff1;
    if (func_ov003_02211980(actor, vector, 0x57, 6, -9) != 7) {
        return 11;
    }
    int layouts = check_point_layouts();
    if (layouts) {
        return layouts;
    }
    return failed;
}
