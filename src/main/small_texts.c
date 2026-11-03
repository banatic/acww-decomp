/* small_texts: 21 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020821bc @ 0x020821bc, 0x18 bytes, Thumb
 * func_020821a4 @ 0x020821a4, 0x18 bytes, Thumb
 * func_02082184 @ 0x02082184, 0x20 bytes, Thumb
 * func_02082180 @ 0x02082180, 0x4 bytes, Thumb
 * func_0208217c @ 0x0208217c, 0x4 bytes, Thumb
 * func_02082164 @ 0x02082164, 0x18 bytes, Thumb
 * func_0208214c @ 0x0208214c, 0x18 bytes, Thumb
 * func_0208212c @ 0x0208212c, 0x20 bytes, Thumb
 * func_02082128 @ 0x02082128, 0x4 bytes, Thumb
 * func_02082114 @ 0x02082114, 0x14 bytes, Thumb
 * func_02082110 @ 0x02082110, 0x4 bytes, Thumb
 * func_020820f8 @ 0x020820f8, 0x18 bytes, Thumb
 * func_020820e0 @ 0x020820e0, 0x18 bytes, Thumb
 * func_020820c0 @ 0x020820c0, 0x20 bytes, Thumb
 * func_020820bc @ 0x020820bc, 0x4 bytes, Thumb
 * func_020820b8 @ 0x020820b8, 0x4 bytes, Thumb
 * func_020820a0 @ 0x020820a0, 0x18 bytes, Thumb
 * func_02082088 @ 0x02082088, 0x18 bytes, Thumb
 * func_02082068 @ 0x02082068, 0x20 bytes, Thumb
 * func_02082064 @ 0x02082064, 0x4 bytes, Thumb
 * func_02082060 @ 0x02082060, 0x4 bytes, Thumb
 */

typedef struct Something {
    void *unk_00;
} Something;

struct UnkStruct_0208214c;

struct UnkStruct_0208214c_2 {
    struct UnkStruct_0208214c *data;
};

typedef struct {
    void *unk_00;
} UnkStruct_02082068;

extern void *func_020a8cac(void *obj);
extern char data_020e1904;
extern void *func_020a8c38(void *p);
extern void func_020edb3c(void *p);
extern void *func_020a88ec(void *);
extern unsigned char data_020e1934[];
extern void *func_020a887c(void *);
extern void MI_CpuCopy8(void *r0, int r1, int r2);
extern unsigned char data_020e18d4[];
extern unsigned char data_020e194c[];

void *func_020821bc(void *obj)
{
    func_020a8cac(obj);
    *(void **) obj = (void *) &data_020e1904;
    return obj;
}

Something *func_020821a4(Something *self)
{
    self->unk_00 = (void *) &data_020e1904;
    func_020a8c38((void *) self);
    return self;
}

void *func_02082184(void *self)
{
    *(void **) self = &data_020e1904;
    func_020a8c38(self);
    func_020edb3c(self);
    return self;
}

int func_02082180(void)
{
    return 10;
}

int func_0208217c(int p0)
{
    return ((int) (p0) + (18));
}

unsigned int *func_02082164(unsigned int *obj)
{
    func_020a88ec(obj);
    *obj = (unsigned int) data_020e1934;
    return obj;
}

struct UnkStruct_0208214c_2 *func_0208214c(struct UnkStruct_0208214c_2 *obj)
{
    obj->data = ((struct UnkStruct_0208214c *) data_020e1934);
    func_020a887c((void *) obj);
    return obj;
}

void *func_0208212c(void *obj)
{
    *(void **) obj = (void *) ((int *) data_020e1934);
    func_020a887c(obj);
    func_020edb3c(obj);
    return obj;
}

int func_02082128(void)
{
    return 4;
}

void func_02082114(void *r0, int r1, int r2)
{
    if (r2 < 4) {
    } else {
        r2 = 4;
    }
    r0 = (char *) r0 + 0xe;
    r2 = r2 << 1;
    MI_CpuCopy8(r0, r1, r2);
}

int func_02082110(int p0)
{
    return ((int) (p0) + (14));
}

void *func_020820f8(void *self)
{
    func_020a8cac(self);
    *(void **) self = (void *) data_020e18d4;
    return self;
}

void *func_020820e0(void *arg)
{
    *(void **) arg = ((char *) data_020e18d4);
    func_020a8c38(arg);
    return arg;
}

void *func_020820c0(void *obj)
{
    *(void **) obj = (void *) ((char *) data_020e18d4);
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}

int func_020820bc(void)
{
    return 22;
}

int func_020820b8(int p0)
{
    return ((int) (p0) + (18));
}

void *func_020820a0(void *obj)
{
    func_020a88ec(obj);
    *(void **) obj = (void *) ((int *) data_020e194c);
    return obj;
}

void *func_02082088(void *ptr)
{
    *(void **) ptr = (void *) data_020e194c;
    func_020a887c(ptr);
    return ptr;
}

UnkStruct_02082068 *func_02082068(UnkStruct_02082068 *this)
{
    this->unk_00 = ((char *) data_020e194c);
    func_020a887c(this);
    func_020edb3c(this);
    return this;
}

int func_02082064(void)
{
    return 10;
}

int func_02082060(int p0)
{
    return ((int) (p0) + (14));
}
