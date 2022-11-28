#ifndef __x_optional_h
#define __x_optional_h

#define OPTIONAL_STRUCT(INNER_TYPE) struct {\
    INNER_TYPE result;\
    int        ok;\
}
#define OPTIONAL_TYPEDEF(INNER_TYPE) typedef OPTIONAL_STRUCT(INNER_TYPE) Optional$##INNER_TYPE;

#define OPTIONAL_DERIVE_PRINT(INNER_TYPE,RESULT_EXPANSION) int print_option_##INNER_TYPE(\
    Optional$##INNER_TYPE self\
){\
    printf("{\"_type\":\"Optional\",\"_generic\":\"" #INNER_TYPE "\",\"result\":\"" #RESULT_EXPANSION "\",\"ok\":\"%d\"}\n",self.result,self.ok);\
    printf("Optional<" #INNER_TYPE ">{.result=" #RESULT_EXPANSION ",.ok=%d}\n",self.result,self.ok);\
    return 1;\
}

#endif