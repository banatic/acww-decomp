/* func_02011e48 @ 0x02011e48, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021c1284;
void func_02011d28(void *);
int func_02011c28(void *, int);
void func_02011b38(void *, int);
void func_02011bb0(void *);
int func_02011bc8(void *);
void func_02011af8(void *, int);
void func_02011b98(void *);
int func_02011ed4(void);
int func_0208ff98(void);
void func_02011d90(int, int, int, int);

void func_02011e48(int a, int b)
{
    void *p = &data_021c1284;

    func_02011d28(p);
    if (func_02011c28(&data_021c1284, 4) != 0) {
        func_02011b38(p, b);
    }
    func_02011bb0(p);
    if (func_02011bc8(p) != 0) {
        func_02011af8(p, b);
    }
    func_02011b98(p);
    if (func_02011ed4() == 2 && func_0208ff98() != 0) {
        func_02011d90(a, 1, 0, b);
    }
}
