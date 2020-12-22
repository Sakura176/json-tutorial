/*
 * @Author: Milo Yip
 * @Date: 2020-12-16 19:02:18
 * @LastEditTime: 2020-12-22 15:23:30
 * @LastEditors: 不摇碧莲
 * @Description: 参考 lept_parse_null() 的实现和调用方法，解析true和false值
 * @FilePath: /json-tutorial/tutorial01/leptjson.c
 * @
 */
#include "leptjson.h"
#include <assert.h> /* assert() */
#include <stdlib.h> /* NULL */

#define EXPECT(c, ch)             \
    do                            \
    {                             \
        assert(*c->json == (ch)); \
        c->json++;                \
    } while (0)

/**
 * @description: 结构体，用于存储JSON文件的内容
 * @param {const char* json} 记录json文本内容
 */
typedef struct
{
    const char *json;
} lept_context;

/**
 * @description: 检测是否存在空格
 * @param lept_context* 结构体指针
 */
static void lept_parse_whitespace(lept_context *c)
{
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

/**
 * @description: 检查值是否为 null
 * @param lept_context* 结构体指针
 * @param lept_value* 结构体的值类型
 * @return int
 */
static int lept_parse_null(lept_context *c, lept_value *v)
{
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_NULL;
    return LEPT_PARSE_OK;
}

/**
 * @description: 检查值是否为 true
 * @param lept_context* 结构体指针
 * @param lept_value* 结构体的值类型
 * @return int
 */
static int lept_parse_true(lept_context *c, lept_value *v)
{
    EXPECT(c, 't');
    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_TRUE;
    return LEPT_PARSE_OK;
}

/**
 * @description: 检查值是否为 false
 * @param lept_context* 结构体指针
 * @param lept_value* 结构体的值类型
 * @return int
 */
static int lept_parse_false(lept_context *c, lept_value *v)
{
    EXPECT(c, 'f');
    if (c->json[0] != "a" || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 4;
    v->type = LEPT_FALSE;
    return LEPT_PARSE_OK;
}

static int lept_parse_value(lept_context *c, lept_value *v)
{
    switch (*c->json)
    {
    case 'n':
        return lept_parse_null(c, v);
    case 't':
        return lept_parse_true(c, v);
    case 'f':
        return lept_parse_false(c, v);
    case '\0':
        return LEPT_PARSE_EXPECT_VALUE;
    default:
        return LEPT_PARSE_INVALID_VALUE;
    }
}

int lept_parse(lept_value *v, const char *json)
{
    lept_context c;
    int ret;
    assert(v != NULL);
    c.json = json;
    v->type = LEPT_NULL;
    lept_parse_whitespace(&c);
    if ((ret = lept_parse_value(&c, v)) == LEPT_PARSE_OK)
    {
        lept_parse_whitespace(&c);
        if (*c.json != '\0')
            ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
    }
    return ret;
}

lept_type lept_get_type(const lept_value *v)
{
    assert(v != NULL);
    return v->type;
}
