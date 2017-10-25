#ifndef __S2J_H__
#define __S2H_H__
/*   */
#include<cJSON.h>
#include<string.h>
#include"s2jdef.h"
/*                       ss  */
#ifdef __cplusplus
extern "C" {
#endif

#define S2J_SW_VERSION "1.0.2"
#define s2j_create_json_obj(json_obj) \
	S2J_CREATE_JSON_OBJECT(json_obj)
#define s2j_delete_json_obj(json_obj) \
	S2J_DELETE_JSON_OBJECT(json_obj)


#define s2j_json_set_basic_element(to_json,from_struct,type,element) \
	S2J_JSON_SET_BASIC_ELEMENT(to_json,from_struct,type,element)

#define s2j_json_set_array_element(to_json,from_struct,type,element,size) \
	S2J_JSON_SET_ARRAY_ELEMENT(to_json,from_struct,type,element,size)

#define s2j_json_set_struct_element(child_json,to_json,child_struct,\
        type,element) \
	S2J_JSON_SET_STRUCT_ELEMENT(child_json,to_json,child_struct,type,element)

#define s2j_create_struct_obj(struct_obj,type) \
	S2J_CREATE_STRUCT_OBJECT(struct_obj,type)

#define s2j_delete_struct_obj(struct_obj) \
	S2J_DELETE_STRUCT_OBJECT(struct_obj)

#define s2j_struct_get_basic_element(to_struct,from_json,type,element) \
	S2J_STRUCT_GET_BASIC_ELEMENT(to_struct,from_json,type,element)

#define s2j_struct_get_array_element(to_struct,from_json,type,element) \
	S2J_STRUCT_GET_ARRAY_ElEMENT(to_struct,from_json,type,element)

#define s2j_struct_get_struct_element(child_struct,to_struct,child_json,from_json,type,element) \
	S2J_STRUCT_GET_STRUCT_ELEMENT(child_struct,to_struct,child_json,from_json,type,element)

extern S2JHook s2jHook;
void s2j_init(S2JHook *hook);

#ifdef __cplusplus
}
#endif

#endif
