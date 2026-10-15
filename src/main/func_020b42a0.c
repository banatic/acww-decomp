/* func_020b42a0 @ 0x020b42a0, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern unsigned char data_020e52d0;
extern unsigned char data_021f4dac;

extern void *func_020b4044(void *);
extern void func_020a8164(void *, void *);
extern void func_020b43f4(void *);
extern void *func_020b4344(void *, void *);
extern void *func_020b402c(void *);
extern int func_020b5548(void);
extern void *func_020a8bb8(int, void *);
extern void func_020a8c1c(void *);
extern void func_020b4c40(void *);
extern void func_020b4c28(void *, int);
extern void func_020b4c24(void *, void *);
extern void func_020a94a4(void *);

void *func_020b42a0(void *self, void *data)
{
    volatile unsigned int unused;
    struct {
        unsigned char pad[0x2c];
    } local;
    void *result;

    (void) &unused;
    func_020b4044(&local);
    func_020a8164(&local, &data_020e52d0);
    local.pad[0x1e] = 0;
    func_020b43f4(self);

    result = func_020b4344(&data_021f4dac, &local);
    if (result != 0) {
        func_020a8bb8(func_020b5548(), data);
        func_020a8c1c(data);
        func_020b4c40((char *) self + 0x18f4);
        func_020b4c28((char *) ((volatile char *) self + 0x18f4), func_020b5548());
        func_020b4c24((char *) ((volatile char *) self + 0x18f4), data);
        *(unsigned int *) ((char *) self + 0x1958) = 0;
        *(unsigned int *) ((char *) self + 0x195c) = 0;
        *(unsigned int *) ((char *) self + 0x1960) = 0;
        func_020a94a4((char *) self + 0x1934);
    }

    func_020b402c(&local);
    return result;
}
