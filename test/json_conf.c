/******************************************    *******************************

      > File Name: json_conf.c

      > Author: Ywl

      > Descripsion:

      > Created Time:     Sun 01 Jul 2018 11:47:41 AM CST

      > Modify Time: 

 *********************************    ***************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

#include <json-c/json.h>
#include <json-c/json_object_private.h>


int main()
{
    struct json_object *object = json_object_new_object();
    struct json_object *object1 = json_object_new_object();
    struct json_object *array = json_object_new_array();

    printf("%ld\n", object->_ref_count);

    json_object_object_add(object1, "name", json_object_new_string("ywl"));
    json_object_object_add(object1, "age", json_object_new_int(22));
    json_object_object_add(object, "object", object1);

    json_object_array_add(array, json_object_new_int(1995));

    json_object_object_add(object, "int", json_object_new_int(123));
    json_object_object_add(object, "bool", json_object_new_boolean(1));
    json_object_object_add(object, "string", json_object_new_string("centos"));
    json_object_object_add(object, "double", json_object_new_double(123.999));
    json_object_object_add(object, "array", array);

    size_t len = 0;
    printf("%s\n", json_object_to_json_string_length(object, JSON_C_TO_STRING_NOSLASHESCAPE, &len));
    printf("json_string_len : %ld\n", len);
#if 1
    json_object_to_file_ext("test.json", object, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY);

    object = json_object_from_file("test.json");
    printf("json-string : \n %s\n", json_object_to_json_string_ext(object, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
#endif

    printf("%ld\n", object1->_ref_count);
    json_object_put(object);
    json_object_object_add(object1, "age1", json_object_new_int(98));
    json_object_object_add(object1, "age2", json_object_new_int(1024));
    printf("json-string2 : \n %s\n", json_object_to_json_string_ext(object1, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
    json_object_put(object1);
    json_object_put(array);
    //json_object_put(object);
    return 0;
}
