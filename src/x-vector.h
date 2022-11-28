#ifndef __x_vector_h
#define __x_vector_h


#define VECTOR_INLINE_FOREACH(INDEX,VECTOR,RECEIVER_BLOCK) {\
    int INDEX=0;\
    while(INDEX<VECTOR.length){\
        RECEIVER_BLOCK \
        INDEX++;\
    }\
}

#define VECTOR_STRUCT(INNER_TYPE) struct {\
    INNER_TYPE* buffer;\
    int         capacity;\
    int         length;\
}
#define VECTOR_TYPEDEF(INNER_TYPE) typedef VECTOR_STRUCT(INNER_TYPE) Vector$##INNER_TYPE;

#define VECTOR_DERIVE_ALLOC(INNER_TYPE) Vector$##INNER_TYPE vector$##INNER_TYPE##_alloc(){\
    int capacity=0;\
    Vector$##INNER_TYPE self={\
        .buffer=(INNER_TYPE*)malloc(capacity*sizeof(INNER_TYPE)),\
        .length=0,\
        .capacity=0\
    };\
    return self;\
}
#define VECTOR_DERIVE_INIT(INNER_TYPE) Vector$##INNER_TYPE vector$##INNER_TYPE##_init(\
    INNER_TYPE* buffer,int buffer_length\
){\
    int capacity=buffer_length;\
    Vector$##INNER_TYPE self={\
        .buffer=(INNER_TYPE*)malloc(buffer_length*sizeof(INNER_TYPE)),\
        .length=buffer_length,\
        .capacity=buffer_length\
    };\
    VECTOR_INLINE_FOREACH(index,self,{\
        self.buffer[index]=buffer[index];\
    })\
    return self;\
}
#define VECTOR_DERIVE_FREE(INNER_TYPE) Vector$##INNER_TYPE vector$##INNER_TYPE##_free(\
    Vector$##INNER_TYPE self\
){\
    free(self.buffer);\
    self.length=0;\
    self.capacity=0;\
    return self;\
}
#define VECTOR_DERIVE_MAP(INNER_TYPE) Vector$##INNER_TYPE vector$##INNER_TYPE##_map(\
    Vector$##INNER_TYPE self,INNER_TYPE(*mapper)(INNER_TYPE value,int index,Vector$##INNER_TYPE vector)\
){\
    int i=0;\
    while(i<self.length){\
        self.buffer[i]=mapper(self.buffer[i],i,self);\
        i++;\
    }\
    return self;\
}


#define VECTOR_DERIVE_PRINT(INNER_TYPE,RESULT_EXPANSION) int vector$##INNER_TYPE##_print(\
    Vector$##INNER_TYPE self\
){\
    printf("Vector<" #INNER_TYPE ">{.buffer=[");\
    for(int i=0;i<self.length;i++){\
        printf("" #RESULT_EXPANSION,self.buffer[i]);\
        if(i<(self.length-1)){\
            printf(",");\
        }\
    }\
    printf("],.length=%d,.capacity=%d}\n",self.length,self.capacity);\
    return 1;\
}
#define VECTOR_DERIVE_PUSH(INNER_TYPE) Vector$##INNER_TYPE vector$##INNER_TYPE##_push(\
    Vector$##INNER_TYPE self, INNER_TYPE item\
){\
    int new_length=self.length+1;\
    if(new_length>self.capacity){\
        int new_capacity=self.capacity*2 + 1;\
        INNER_TYPE* new_buffer=(INNER_TYPE*)malloc(new_capacity*sizeof(INNER_TYPE));\
        for(int i=0;i<self.length;i++){\
            new_buffer[i]=self.buffer[i];\
        }\
        free(self.buffer);\
        self.buffer=new_buffer;\
        self.capacity=new_capacity;\
    }\
    self.length=new_length;\
    self.buffer[self.length - 1] = item;\
    return self;\
}
#define VECTOR_DERIVE_COPY(INNER_TYPE) Vector$##INNER_TYPE vector$##INNER_TYPE##_copy(\
    Vector$##INNER_TYPE self\
){\
    Vector$##INNER_TYPE copy=vector$##INNER_TYPE##_alloc();\
    copy.capacity=self.capacity;\
    copy.length=self.length;\
    copy.buffer=(INNER_TYPE*)malloc(copy.capacity*sizeof(INNER_TYPE));\
    for(int i=0;i<self.length;i++){\
        copy.buffer[i]=self.buffer[i];\
    }\
    return copy;\
}
#define VECTOR_DERIVE_CONCAT(INNER_TYPE) Vector$##INNER_TYPE vector$##INNER_TYPE##_concat(\
    Vector$##INNER_TYPE self,\
    Vector$##INNER_TYPE other\
){\
    Vector$##INNER_TYPE copy=vector$##INNER_TYPE##_copy(self);\
    copy.length=self.length+other.length;\
    copy.capacity=copy.length+1;\
    copy.buffer=(INNER_TYPE*)malloc(copy.capacity*sizeof(INNER_TYPE));\
    for(int i=0;i<self.length;i++){\
        copy.buffer[i]=self.buffer[i];\
    }\
    for(int i=0;i<other.length;i++){\
        copy.buffer[self.length+i]=other.buffer[i];\
    }\
    vector$##INNER_TYPE##_free(self);\
    vector$##INNER_TYPE##_free(other);\
    return copy;\
}
#endif