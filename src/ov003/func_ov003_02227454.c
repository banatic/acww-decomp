/* func_ov003_02227454 @ 0x02227454, 0x168 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_020da13c;
extern int data_ov003_0223bc7c;

void *func_020edf70(unsigned int n);
void func_020ee660(void *p);
void func_02138d6c(void *p, int n, int sz, void (*ctor)(void *), void (*dtor)(void *));
void func_02055444(void *p);
void func_ov003_02223b8c(void *p);
void func_02055764(void *p);
void func_0205577c(void *p);

void *func_ov003_02227454(void)
{
    char *p = (char *) func_020edf70(0x6a70);
    if (p != 0) {
        func_020ee660(p);
        *(int *) p = (int) &data_020da13c;
        *(int *) p = (int) &data_ov003_0223bc7c;
        func_02138d6c(p + 0x174, 0x12, 0x9c, func_0205577c, func_02055764);
        func_02138d6c(p + 0xc6c, 6, 0x9c, func_0205577c, func_02055764);
        func_02138d6c(p + 0x1014, 3, 0x9c, func_0205577c, func_02055764);
        func_02138d6c(p + 0x11e8, 6, 0x9c, func_0205577c, func_02055764);
        func_02138d6c(p + 0x1590, 0x28, 0x9c, func_0205577c, func_02055764);
        func_02138d6c(p + 0x2df0, 4, 0x9c, func_0205577c, func_02055764);
        func_02138d6c(p + 0x3068, 0x20, 0x9c, func_0205577c, func_02055764);
        func_02138d6c(p + 0x43e8, 5, 0x9c, func_0205577c, func_02055764);
        func_02138d6c(p + 0x4708, 2, 0x9c, func_0205577c, func_02055764);
        func_02138d6c(p + 0x4840, 2, 0x9c, func_0205577c, func_02055764);
        func_02138d6c(p + 0x49a8, 2, 0x9c, func_0205577c, func_02055764);
        func_02055444(p + 0x4ae0);
        func_02055444(p + 0x4af0);
        func_02055444(p + 0x4b00);
        func_02055444(p + 0x4b10);
        func_ov003_02223b8c(p + 0x4b20);
    }
    return p;
}
