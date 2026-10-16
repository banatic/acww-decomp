/* The answers a shop change waits for (shop_answers.h). */
#include "shop_answers.h"

#include "clean.h"
#include "main/session.h"

static_assert(sizeof(ShopAnswers) == 2, "shop answers");

extern NetSession *data_020ccf94;
extern ShopAnswers data_021f49ec;

/* func_020afc5c: whether every answer came (always, when not linked). */
int ShopAnswers_AllCameIfLinked(void)
{
    if (Session_IsLinked(data_020ccf94) != 0) {
        return ShopAnswers_AllCame(&data_021f49ec);
    }
    return 1;
}
CLEAN_AS(func_020afc5c, ShopAnswers_AllCameIfLinked)

/* func_020b01dc: an answer came (counted up to the number expected); whether all have. */
int ShopAnswers_Count(ShopAnswers *answers)
{
    if (answers->received < answers->expected) {
        answers->received = (u8) (answers->received + 1);
    }
    return ShopAnswers_AllCame(answers);
}
CLEAN_AS(func_020b01dc, ShopAnswers_Count)

/* func_020b01f0 */
int ShopAnswers_AllCame(ShopAnswers *answers)
{
    return answers->received >= answers->expected;
}
CLEAN_AS(func_020b01f0, ShopAnswers_AllCame)

/* func_020b0200: none came yet; one to wait for from each of the session's other players
 * when linked, none otherwise.
 * QUIRK: linked with no players, the count wraps to 255. */
void ShopAnswers_Expect(ShopAnswers *answers)
{
    answers->received = 0;
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session) != 0) {
        answers->expected = (u8) (session->player_count - 1);
    } else {
        answers->expected = 0;
    }
}
CLEAN_AS(func_020b0200, ShopAnswers_Expect)

/* func_020b0234 */
void ShopAnswers_Clear(ShopAnswers *answers)
{
    answers->expected = 0;
    answers->received = 0;
}
CLEAN_AS(func_020b0234, ShopAnswers_Clear)

/* func_020b023c: the destructor (registered for data_021f49ec): clears it and returns it. */
int ShopAnswers_Destruct(ShopAnswers *answers)
{
    ShopAnswers_Clear(answers);
    return (int) (uintptr_t) answers;
}
CLEAN_AS(func_020b023c, ShopAnswers_Destruct)

/* func_020b024c: the constructor: cleared. */
ShopAnswers *ShopAnswers_Construct(ShopAnswers *answers)
{
    ShopAnswers_Clear(answers);
    return answers;
}
CLEAN_AS(func_020b024c, ShopAnswers_Construct)
