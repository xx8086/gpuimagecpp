//
//  lock.h
//  GPUImageCPP
//
//  Created by liu on 2018/9/11.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef lock_h
#define lock_h
#include <atomic>

namespace gpuimagecpp {
    class spin_lock{//自旋锁
    public:
        spin_lock(){
            _flg.clear(std::memory_order_release);
        }
        virtual ~spin_lock(){};
        void set_try_counts(int counts){_try_counts = counts;}
    public:
        inline  void lock(){//一直尝试直到成功.
            while (_flg.test_and_set(std::memory_order_acquire));
        }
        
        inline  bool try_lock(){//只尝试_try_counts次
            int counts = _try_counts;
            for (; counts > 0 && _flg.test_and_set(std::memory_order_acquire); --counts);
            return counts > 0 ? true : false;
        }
        
        inline void unlock(){
            _flg.clear(std::memory_order_release);
        }
        
    private:
        spin_lock(const spin_lock&);
        spin_lock(spin_lock&&);
        spin_lock& operator=(const spin_lock&);
        spin_lock& operator=(spin_lock&&);
        
    private:
        int _try_counts = 100;
        std::atomic_flag _flg;
    };
    
    class auto_lock{
    public:
        auto_lock(){_lock.lock();}
        ~auto_lock(){_lock.unlock();}
    private:
        static spin_lock _lock;
    };
    
    spin_lock auto_lock::_lock;
    
}

#endif /* lock_h */
