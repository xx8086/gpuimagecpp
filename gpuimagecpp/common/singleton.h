//
//  singleton.h
//  GPUImageCPP
//
//  Created by liu on 2018/9/11.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef singleton_h
#define singleton_h
namespace gpuimagecpp {
    template <class T>
    class Singleton{
    public:
        inline static T* get_instance(){
            if (_s_instance_prt == nullptr){
                _s_instance_prt = new T();
                //atexit(destroy_instance);
            }
            
            return _s_instance_prt;
        }
        
        inline static void destroy_instance(){
            if (_s_instance_prt != nullptr){
                delete _s_instance_prt;
                _s_instance_prt = nullptr;
            }
            _s_instance_prt = nullptr;
        }
        
    protected:
        Singleton() {}
        Singleton(const Singleton& sing) {}
        Singleton& operator=(const Singleton&) {}
        
        virtual ~Singleton(){
        }
    private:
        static T* _s_instance_prt;
    };
    
    template <class T>
    T* Singleton<T>::_s_instance_prt = nullptr;
}

#endif /* singleton_h */
