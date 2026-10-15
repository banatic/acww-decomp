/* func_02059e1c @ 0x02059e1c, 0x3c0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} UnkStruct_02059e1c;

extern "C" {

// 0x02063ccc / 0x02063cc8: constructor and destructor of the 8-byte object.
extern void func_02063ccc(UnkStruct_02059e1c *, int, int);
extern void func_02063cc8(void *);
// 0x020638d4: writes a 16-bit handle through its first argument.
extern void func_020638d4(unsigned short *, const UnkStruct_02059e1c *, int, int, int, int, int *);
// 0x02063884: the single-argument twin of mk, used by the retry path.
extern void func_02063884(unsigned short *, const UnkStruct_02059e1c *);
// 0x020644cc: ARM; returns an index in [0, n).
extern int func_020644cc(int);
// 0x02138bb0: __register_global_object(object, destructor, chain node).
extern void __register_global_object(void *, void *, void *);
// 0x02098868
extern int func_02098868(void *, int);
// 0x0205a240: the tail call this function's result comes from.
extern int func_0205a240(void *, unsigned char, int, int, unsigned short *, int);

// Static-initialisation guards, one per case.
extern int data_021c95f4, data_021c95f8, data_021c95ec;
// The lazily-constructed object tables.
extern UnkStruct_02059e1c data_021c96ec[3], data_021c96d4[3], data_021c972c[9];
// Destructor chain nodes, one per registered object.
extern void *data_021c9650, *data_021c962c, *data_021c9644;
extern void *data_021c9620, *data_021c9698, *data_021c96b0;
extern void *data_021c9608, *data_021c9668, *data_021c9638, *data_021c965c, *data_021c9680, *data_021c96bc, *data_021c95fc,
    *data_021c9614, *data_021c9674;

extern void *data_021dc7bc;
extern void *data_020cbfe4[];
extern void *data_020dd3c4;

int func_02059e1c(unsigned int a, int b, int c);
}

#define INVALID 0xfff1

int func_02059e1c(unsigned int a, int b, int c)
{
    // ret and h1-h6 are adjacent u16 stack slots, so their declaration order matters.
    unsigned short ret;
    unsigned short h1, h2, h3, h4, h5, h6;
    UnkStruct_02059e1c o1;
    int outv;

    if (a < 1) {
        return 0;
    }
    if (a > 5) {
        return 0;
    }

    ret = INVALID;
    func_020644cc(3);
    func_020644cc(3);

    switch (a) {
        case 1: {
            UnkStruct_02059e1c t;
            func_02063ccc(&t, 0, 0);
            func_020638d4(&h1, &t, 0, 0, 1, 1, 0);
            ret = h1;
            func_02063cc8(&t);
            break;
        }
        case 2: {
            UnkStruct_02059e1c t;
            if (!(data_021c95f4 & 1)) {
                func_02063ccc(&data_021c96ec[0], 0, 1);
                __register_global_object((void *) (&data_021c96ec[0]), (((void *) func_02063cc8)), (void *) (&data_021c9650));
                func_02063ccc(&data_021c96ec[1], 0, 2);
                __register_global_object((void *) (&data_021c96ec[1]), (((void *) func_02063cc8)), (void *) (&data_021c962c));
                func_02063ccc(&data_021c96ec[2], 0, 3);
                __register_global_object((void *) (&data_021c96ec[2]), (((void *) func_02063cc8)), (void *) (&data_021c9644));
                data_021c95f4 |= 1;
            }
            t = data_021c96ec[func_020644cc(3)];
            func_020638d4(&h2, &t, 0, 0, 1, 1, 0);
            ret = h2;
            func_02063cc8(&t);
            break;
        }
        case 3: {
            UnkStruct_02059e1c t;
            if (!(data_021c95f8 & 1)) {
                func_02063ccc(&data_021c96d4[0], 0, 0);
                __register_global_object((void *) (&data_021c96d4[0]), (((void *) func_02063cc8)), (void *) (&data_021c9620));
                func_02063ccc(&data_021c96d4[1], 4, 0);
                __register_global_object((void *) (&data_021c96d4[1]), (((void *) func_02063cc8)), (void *) (&data_021c9698));
                func_02063ccc(&data_021c96d4[2], 3, 0);
                __register_global_object((void *) (&data_021c96d4[2]), (((void *) func_02063cc8)), (void *) (&data_021c96b0));
                data_021c95f8 |= 1;
            }
            t = data_021c96d4[func_020644cc(3)];
            func_020638d4(&h3, &t, 0, 0, 1, 1, 0);
            ret = h3;
            func_02063cc8(&t);
            break;
        }
        case 4: {
            UnkStruct_02059e1c t;
            if (!(data_021c95ec & 1)) {
                func_02063ccc(&data_021c972c[0], 0, 1);
                __register_global_object((void *) (&data_021c972c[0]), (((void *) func_02063cc8)), (void *) (&data_021c9608));
                func_02063ccc(&data_021c972c[1], 0, 2);
                __register_global_object((void *) (&data_021c972c[1]), (((void *) func_02063cc8)), (void *) (&data_021c9668));
                func_02063ccc(&data_021c972c[2], 0, 3);
                __register_global_object((void *) (&data_021c972c[2]), (((void *) func_02063cc8)), (void *) (&data_021c9638));
                func_02063ccc(&data_021c972c[3], 4, 1);
                __register_global_object((void *) (&data_021c972c[3]), (((void *) func_02063cc8)), (void *) (&data_021c965c));
                func_02063ccc(&data_021c972c[4], 4, 2);
                __register_global_object((void *) (&data_021c972c[4]), (((void *) func_02063cc8)), (void *) (&data_021c9680));
                func_02063ccc(&data_021c972c[5], 4, 3);
                __register_global_object((void *) (&data_021c972c[5]), (((void *) func_02063cc8)), (void *) (&data_021c96bc));
                func_02063ccc(&data_021c972c[6], 3, 1);
                __register_global_object((void *) (&data_021c972c[6]), (((void *) func_02063cc8)), (void *) (&data_021c95fc));
                func_02063ccc(&data_021c972c[7], 3, 2);
                __register_global_object((void *) (&data_021c972c[7]), (((void *) func_02063cc8)), (void *) (&data_021c9614));
                func_02063ccc(&data_021c972c[8], 3, 3);
                __register_global_object((void *) (&data_021c972c[8]), (((void *) func_02063cc8)), (void *) (&data_021c9674));
                data_021c95ec |= 1;
            }
            t = data_021c972c[func_020644cc(9)];
            func_020638d4(&h4, &t, 0, 0, 1, 1, 0);
            ret = h4;
            func_02063cc8(&t);
            break;
        }
        default: {
            UnkStruct_02059e1c t;
            void *p;
            int n;

            n = func_02098868(&data_021dc7bc, b);
            p = data_020cbfe4[func_020644cc(3)];
            func_02063ccc(&o1, (int) p, 0);
            t = o1;
            func_020638d4(&h5, &t, n, 0, 1, 1, &outv);
            ret = h5;
            func_02063cc8(&t);
            if (ret == INVALID) {
                UnkStruct_02059e1c t2;
                func_02063ccc(&t2, (int) p, outv);
                func_02063884(&h6, &t2);
                ret = h6;
                func_02063cc8(&t2);
            }
            func_02063cc8(&o1);
            break;
        }
    }

    return func_0205a240(&data_020dd3c4, (unsigned char) func_020644cc(3), b, c, &ret, -1);
}
