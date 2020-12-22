#ifndef LEPTJSON_H__
#define LEPTJSON_H__

// 枚举，表示json文件的几种数据类型
typedef enum
{
    LEPT_NULL,
    LEPT_FALSE,
    LEPT_TRUE,
    LEPT_NUMBER,
    LEPT_STRING,
    LEPT_ARRAY,
    LEPT_OBJECT
} lept_type;

// 结构体， 用于储存json数据的类型和数量
typedef struct
{
    double n;
    lept_type type; // 枚举来储存类型
} lept_value;

enum
{
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR,
    LEPT_PARSE_NUMBER_TOO_BIG
};

int lept_parse(lept_value *v, const char *json);

lept_type lept_get_type(const lept_value *v);

double lept_get_number(const lept_value *v);

#endif /* LEPTJSON_H__ */
