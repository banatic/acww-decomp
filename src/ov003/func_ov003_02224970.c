/* func_ov003_02224970 @ 0x02224970, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c80bc;
extern void *data_021c67a4;
extern int data_ov003_0223cfe4;
void func_ov003_022249cc(void *self, void *a);
void func_ov003_022214b4(void *p);
void func_ov003_0222399c(void *p);

int func_ov003_02224970(char *self)
{
    void *a = data_021c80bc;
    void *b = data_021c67a4;
    if (a != 0 && b != 0) {
        *(int *) (self + 0x6a6c) = (*(int *) (self + 0x6a6c) + 1) % 0x3c;
        func_ov003_022249cc(self, a);
        func_ov003_022214b4(&data_ov003_0223cfe4);
        func_ov003_0222399c(self + 0x4b20);
    }
    return 1;
}
