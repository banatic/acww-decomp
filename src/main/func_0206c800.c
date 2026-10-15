/* func_0206c800 @ 0x0206c800, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0206c800 {
    char pad_00[0x2c];
    void *data;
} UnkStruct_0206c800;

typedef struct Caller {
    char pad_00[0xc];
    int (*func)(void *);
} Caller;

extern int func_0206786c(void *p);
extern void func_020a9334(void *obj, int v);
extern void func_020a7994(void *p, int v);

void func_0206c800(UnkStruct_0206c800 *obj)
{
    func_0206786c(obj->data);
    {
        void *p = (char *) obj->data + 0x1d2c;
        Caller *q = *(Caller **) p;
        int ret = q->func(p);
        func_020a9334(obj, ret);
    }
    {
        void *p = (char *) obj->data + 0x1d2c;
        Caller *q = *(Caller **) p;
        int ret = q->func(p);
        func_020a7994((char *) obj->data + 0x1a58, ret);
    }
    *(int *) ((char *) obj->data + 0x1a60) = 0;
}
