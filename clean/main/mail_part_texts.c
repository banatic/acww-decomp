/* The three 8-bit texts of a letter's parts (mail_part_texts.h). */
#include "mail_part_texts.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "text_base.h"

static_assert(offsetof(MailSuperText, text) == 0x12, "super characters");
static_assert(sizeof(MailSuperText) == 0x28, "super");
static_assert(offsetof(MailMsgText, text) == 0x12, "msg characters");
static_assert(offsetof(MailPsText, text) == 0x12, "ps characters");
static_assert(sizeof(MailPsText) == 0x34, "ps");

/* The classes' vtables. */
extern const TextVtable data_020df228; /* MailPsText */
extern const TextVtable data_020df210; /* MailMsgText */
extern const TextVtable data_020df240; /* MailSuperText */

/* The destructor's work: the class's vtable, then the 8-bit text base's destructor. */
static void mail_part_text_destroy(void *text, const TextVtable *vtable)
{
    *(const TextVtable **) text = vtable;
    TextBase_Destruct((TextBase *) text);
}

/* The constructor's work: the 8-bit text base's constructor, the class's vtable, then the text
 * emptied. */
static void mail_part_text_build(void *text, const TextVtable *vtable)
{
    TextBase_Construct(text);
    *(const TextVtable **) text = vtable;
    TextBase_Clear(text);
}

/* ---- MailPsText */

/* func_0206d9f8 (vtable slot 3): the address of the characters. */
int MailPsText_Buffer(int text)
{
    return text + (int) offsetof(MailPsText, text);
}
CLEAN_AS(func_0206d9f8, MailPsText_Buffer)

/* func_0206d9fc (vtable slot 2): the capacity. */
int MailPsText_Capacity(void)
{
    return MAIL_PS_TEXT_CAPACITY;
}
CLEAN_AS(func_0206d9fc, MailPsText_Capacity)

/* func_0206da00 (vtable slot 1): destroyed (MailPsText_Destruct) and freed. */
MailPsText *MailPsText_Delete(MailPsText *text)
{
    mail_part_text_destroy(text, &data_020df228);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_0206da00, MailPsText_Delete)

/* func_0206da20 (vtable slot 0): the destructor. */
MailPsText *MailPsText_Destruct(MailPsText *text)
{
    mail_part_text_destroy(text, &data_020df228);
    return text;
}
CLEAN_AS(func_0206da20, MailPsText_Destruct)

/* func_0206da38: an empty text. */
MailPsText *MailPsText_Construct(MailPsText *text)
{
    mail_part_text_build(text, &data_020df228);
    return text;
}
CLEAN_AS(func_0206da38, MailPsText_Construct)

/* ---- MailMsgText */

/* func_0206da58 (vtable slot 3): the address of the characters. */
int MailMsgText_Buffer(int text)
{
    return text + (int) offsetof(MailMsgText, text);
}
CLEAN_AS(func_0206da58, MailMsgText_Buffer)

/* func_0206da5c (vtable slot 2): the capacity. */
int MailMsgText_Capacity(void)
{
    return MAIL_MSG_TEXT_CAPACITY;
}
CLEAN_AS(func_0206da5c, MailMsgText_Capacity)

/* func_0206da60 (vtable slot 1): destroyed (MailMsgText_Destruct) and freed. */
MailMsgText *MailMsgText_Delete(MailMsgText *text)
{
    mail_part_text_destroy(text, &data_020df210);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_0206da60, MailMsgText_Delete)

/* func_0206da80 (vtable slot 0): the destructor. */
MailMsgText *MailMsgText_Destruct(MailMsgText *text)
{
    mail_part_text_destroy(text, &data_020df210);
    return text;
}
CLEAN_AS(func_0206da80, MailMsgText_Destruct)

/* func_0206da98: an empty text. */
MailMsgText *MailMsgText_Construct(MailMsgText *text)
{
    mail_part_text_build(text, &data_020df210);
    return text;
}
CLEAN_AS(func_0206da98, MailMsgText_Construct)

/* ---- MailSuperText */

/* func_0206dab8 (vtable slot 3): the address of the characters. */
int MailSuperText_Buffer(int text)
{
    return text + (int) offsetof(MailSuperText, text);
}
CLEAN_AS(func_0206dab8, MailSuperText_Buffer)

/* func_0206dabc (vtable slot 2): the capacity. */
int MailSuperText_Capacity(void)
{
    return MAIL_SUPER_TEXT_CAPACITY;
}
CLEAN_AS(func_0206dabc, MailSuperText_Capacity)

/* func_0206dac0 (vtable slot 1): destroyed (MailSuperText_Destruct) and freed. */
MailSuperText *MailSuperText_Delete(MailSuperText *text)
{
    mail_part_text_destroy(text, &data_020df240);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_0206dac0, MailSuperText_Delete)

/* func_0206dae0 (vtable slot 0): the destructor. */
MailSuperText *MailSuperText_Destruct(MailSuperText *text)
{
    mail_part_text_destroy(text, &data_020df240);
    return text;
}
CLEAN_AS(func_0206dae0, MailSuperText_Destruct)

/* func_0206daf8: an empty text. */
MailSuperText *MailSuperText_Construct(MailSuperText *text)
{
    mail_part_text_build(text, &data_020df240);
    return text;
}
CLEAN_AS(func_0206daf8, MailSuperText_Construct)
