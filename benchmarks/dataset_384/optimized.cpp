#include <cctype>
#include <cstddef>
extern "C" int bstr_util_mem_index_of_mem_nocasenorzero(const void *data1,size_t len1,const void *data2,size_t len2){
    const unsigned char* d1=(const unsigned char*)data1;
    const unsigned char* d2=(const unsigned char*)data2;
    size_t i,j;
    for(i=0;i<len1;i++){
        size_t k=i;
        if(d1[i]==0){
            continue;
        }
        for(j=0;(j<len2)&&(k<len1);j++,k++){
            if(d1[k]==0){
                j--;
                continue;
            }
            if(toupper(d1[k])!=toupper(d2[j])) break;
        }
        if(j==len2) return i;
    }
    return -1;
}
