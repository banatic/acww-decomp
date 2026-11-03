/* scene_heaps_3: 23 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205cb68 @ 0x0205cb68, 0x18 bytes, Thumb
 * func_0205cb4c @ 0x0205cb4c, 0x1c bytes, Thumb
 * func_0205cb34 @ 0x0205cb34, 0x18 bytes, Thumb
 * func_0205cb18 @ 0x0205cb18, 0x1c bytes, Thumb
 * func_0205cb00 @ 0x0205cb00, 0x18 bytes, Thumb
 * func_0205cae4 @ 0x0205cae4, 0x1c bytes, Thumb
 * func_0205cacc @ 0x0205cacc, 0x18 bytes, Thumb
 * func_0205cab0 @ 0x0205cab0, 0x1c bytes, Thumb
 * func_0205ca98 @ 0x0205ca98, 0x18 bytes, Thumb
 * func_0205ca7c @ 0x0205ca7c, 0x1c bytes, Thumb
 * func_0205ca64 @ 0x0205ca64, 0x18 bytes, Thumb
 * func_0205ca48 @ 0x0205ca48, 0x1c bytes, Thumb
 * func_0205ca30 @ 0x0205ca30, 0x18 bytes, Thumb
 * func_0205ca14 @ 0x0205ca14, 0x1c bytes, Thumb
 * func_0205c9fc @ 0x0205c9fc, 0x18 bytes, Thumb
 * func_0205c9e0 @ 0x0205c9e0, 0x1c bytes, Thumb
 * func_0205c9c8 @ 0x0205c9c8, 0x18 bytes, Thumb
 * func_0205c9ac @ 0x0205c9ac, 0x1c bytes, Thumb
 * func_0205c994 @ 0x0205c994, 0x18 bytes, Thumb
 * func_0205c978 @ 0x0205c978, 0x1c bytes, Thumb
 * func_0205c960 @ 0x0205c960, 0x18 bytes, Thumb
 * func_0205c944 @ 0x0205c944, 0x1c bytes, Thumb
 * func_0205c92c @ 0x0205c92c, 0x18 bytes, Thumb
 */

extern void *func_020ea1bc(int size, void *heap);
extern int data_021c9b30;
extern void func_020e9fc8(void *ptr);
extern int data_021c9b2c;
extern int data_021c9b28;
extern int data_021c9b24;
extern int data_021c9b20;
extern int func_020ea0e0(int, void *);
extern int data_021c9b1c;
extern int data_021c9b18;
extern int data_021c9b14;
extern int data_021c9b10;
extern unsigned int data_021c9b0c;
extern int data_021c9b08;
extern int data_021c9b04;

void func_0205cb68(int size, void *heap)
{
    data_021c9b30 = (int) func_020ea1bc(size, heap);
}

void func_0205cb4c(void)
{
    func_020e9fc8((*(void * *) &data_021c9b30));
    (*(void * *) &data_021c9b30) = 0;
}

void func_0205cb34(int size, void *heap)
{
    data_021c9b2c = (int) func_020ea1bc(size, heap);
}

void func_0205cb18(void)
{
    func_020e9fc8((*(void * *) &data_021c9b2c));
    (*(void * *) &data_021c9b2c) = 0;
}

void func_0205cb00(int size, void *heap)
{
    data_021c9b28 = (int) func_020ea1bc(size, heap);
}

void func_0205cae4(void)
{
    func_020e9fc8((void *) data_021c9b28);
    data_021c9b28 = 0;
}

void func_0205cacc(int size, void *heap)
{
    data_021c9b24 = (int) func_020ea1bc(size, heap);
}

void func_0205cab0(void)
{
    func_020e9fc8((*(void * *) &data_021c9b24));
    (*(void * *) &data_021c9b24) = 0;
}

int func_0205ca98(int size, int heapword)
{
    int result;
    result = (int) func_020ea1bc(size, (void *) heapword);
    data_021c9b20 = result;
    return result;
}

void func_0205ca7c(void)
{
    func_020e9fc8((void *) data_021c9b20);
    data_021c9b20 = 0;
}

void func_0205ca64(int argument0, void *argument1)
{
    data_021c9b1c = func_020ea0e0((int) argument0, (void *) argument1);
}

void func_0205ca48(void)
{
    func_020e9fc8((*(void * *) &data_021c9b1c));
    (*(void * *) &data_021c9b1c) = 0;
}

int func_0205ca30(int size, int heapword)
{
    int result;
    result = (int) func_020ea1bc(size, (void *) heapword);
    data_021c9b18 = result;
    return result;
}

void func_0205ca14(void)
{
    func_020e9fc8((*(void * *) &data_021c9b18));
    (*(void * *) &data_021c9b18) = (void *) 0;
}

int func_0205c9fc(int size, int heapword)
{
    int result;
    result = (int) func_020ea1bc(size, (void *) heapword);
    data_021c9b14 = result;
    return result;
}

void func_0205c9e0(void)
{
    func_020e9fc8((*(void * *) &data_021c9b14));
    (*(void * *) &data_021c9b14) = 0;
}

int func_0205c9c8(int size, int heapword)
{
    int result;
    result = (int) func_020ea1bc(size, (void *) heapword);
    data_021c9b10 = result;
    return result;
}

void func_0205c9ac(void)
{
    func_020e9fc8((*(void * *) &data_021c9b10));
    (*(void * *) &data_021c9b10) = 0;
}

int func_0205c994(int size, int heapword)
{
    int result;
    result = (int) func_020ea1bc(size, (void *) heapword);
    data_021c9b0c = result;
    return result;
}

void func_0205c978(void)
{
    func_020e9fc8((*(void * *) &data_021c9b0c));
    (*(void * *) &data_021c9b0c) = 0;
}

int func_0205c960(int size, int heapword)
{
    int result;
    result = (int) func_020ea1bc(size, (void *) heapword);
    data_021c9b08 = result;
    return result;
}

void func_0205c944(void)
{
    func_020e9fc8((void *) data_021c9b08);
    data_021c9b08 = 0;
}

int func_0205c92c(int size, int heapword)
{
    int result;
    result = (int) func_020ea1bc(size, (void *) heapword);
    data_021c9b04 = result;
    return result;
}
