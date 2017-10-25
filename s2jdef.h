#ifndef __S2JDEF_H__
#define __S2JDEF_H__

#include <cJSON.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void *(*malloc_fn)(size_t sz);
    void (*free_fn)(void *ptr);
} S2jHook, *S2jHook_t;

#define S2J_STRUCT_GET_int_ELEMENT(to_struct, from_json, _element) \
    json_temp = cJSON_GetObjectItem(from_json, #_element); \
    if (json_temp) (to_struct)->_element = json_temp->valueint;

#define S2J_STRUCT_GET_string_ELEMENT(to_struct, from_json, _element) \
    json_temp = cJSON_GetObjectItem(from_json, #_element); \
    if (json_temp) strcpy((to_struct)->_element, json_temp->valuestring);

#define S2J_STRUCT_GET_double_ELEMENT(to_struct, from_json, _element) \
    json_temp = cJSON_GetObjectItem(from_json, #_element); \
    if (json_temp) (to_struct)->_element = json_temp->valuedouble;

#define S2J_STRUCT_ARRAY_GET_int_ELEMENT(to_struct, from_json, _element, index) \
    (to_struct)->_element[index] = from_json->valueint;

#define S2J_STRUCT_ARRAY_GET_string_ELEMENT(to_struct, from_json, _element, index) \
    strcpy((to_struct)->_element[index], from_json->valuestring);

#define S2J_STRUCT_ARRAY_GET_double_ELEMENT(to_struct, from_json, _element, index) \
    (to_struct)->_element[index] = from_json->valuedouble;

#define S2J_STRUCT_ARRAY_GET_ELEMENT(to_struct, from_json, type, _element, index) \
    S2J_STRUCT_ARRAY_GET_##type##_ELEMENT(to_struct, from_json, _element, index)

#define S2J_JSON_SET_int_ELEMENT(to_json, from_struct, _element) \
    cJSON_AddNumberToObject(to_json, #_element, (from_struct)->_element);

#define S2J_JSON_SET_double_ELEMENT(to_json, from_struct, _element) \
    cJSON_AddNumberToObject(to_json, #_element, (from_struct)->_element);

#define S2J_JSON_SET_string_ELEMENT(to_json, from_struct, _element) \
    cJSON_AddStringToObject(to_json, #_element, (from_struct)->_element);

#define S2J_JSON_ARRAY_SET_int_ELEMENT(to_json, from_struct, _element, index) \
    cJSON_AddItemToArray(to_json, cJSON_CreateNumber((from_struct)->_element[index]));

#define S2J_JSON_ARRAY_SET_double_ELEMENT(to_json, from_struct, _element, index) \
    cJSON_AddItemToArray(to_json, cJSON_CreateNumber((from_struct)->_element[index]));

#define S2J_JSON_ARRAY_SET_string_ELEMENT(to_json, from_struct, _element, index) \
    cJSON_AddItemToArray(to_json, cJSON_CreateString((from_struct)->_element[index]));

#define S2J_JSON_ARRAY_SET_ELEMENT(to_json, from_struct, type, _element, index) \
    S2J_JSON_ARRAY_SET_##type##_ELEMENT(to_json, from_struct, _element, index)


#define S2J_CREATE_JSON_OBJECT(json_obj) \
    cJSON *json_obj = cJSON_CreateObject();

#define S2J_DELETE_JSON_OBJECT(json_obj) \
    cJSON_Delete(json_obj);

#define S2J_JSON_SET_BASIC_ELEMENT(to_json, from_struct, type, _element) \
    S2J_JSON_SET_##type##_ELEMENT(to_json, from_struct, _element)

#define S2J_JSON_SET_ARRAY_ELEMENT(to_json, from_struct, type, _element, size) \
    { \
        cJSON *array; \
        size_t index = 0; \
        array = cJSON_CreateArray(); \
        if (array) { \
            while (index < size) { \
                S2J_JSON_ARRAY_SET_ELEMENT(array, from_struct, type, _element, index++); \
            } \
            cJSON_AddItemToObject(to_json, #_element, array); \
        } \
    }

#define S2J_JSON_SET_STRUCT_ELEMENT(child_json, to_json, child_struct, from_struct, type, _element) \
    type *child_struct = &((from_struct)->_element); \
    cJSON *child_json = cJSON_CreateObject(); \
    if (child_json) cJSON_AddItemToObject(to_json, #_element, child_json);

#define S2J_CREATE_STRUCT_OBJECT(struct_obj, type) \
    cJSON *json_temp; \
    type *struct_obj = s2jHook.malloc_fn(sizeof(type)); \
    if (struct_obj) memset(struct_obj, 0, sizeof(type));

#define S2J_DELETE_STRUCT_OBJECT(struct_obj) \
    s2jHook.free_fn(struct_obj);

#define S2J_STRUCT_GET_BASIC_ELEMENT(to_struct, from_json, type, _element) \
    S2J_STRUCT_GET_##type##_ELEMENT(to_struct, from_json, _element)

#define S2J_STRUCT_GET_ARRAY_ELEMENT(to_struct, from_json, type, _element) \
    { \
        cJSON *array, *array_element; \
        size_t index = 0, size = 0; \
        array = cJSON_GetObjectItem(from_json, #_element); \
        if (array) { \
            size = cJSON_GetArraySize(array); \
            while (index < size) { \
                array_element = cJSON_GetArrayItem(array, index); \
                if (array_element) S2J_STRUCT_ARRAY_GET_ELEMENT(to_struct, array_element, type, _element, index++); \
            } \
        } \
    }

#define S2J_STRUCT_GET_STRUCT_ELEMENT(child_struct, to_struct, child_json, from_json, type, _element) \
    type *child_struct = &((to_struct)->_element); \
    cJSON *child_json = cJSON_GetObjectItem(from_json, #_element);

#ifdef __cplusplus
}
#endif

#endif /* __S2JDEF_H__ */
