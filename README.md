

* 现有的gpuimage使用起来还是复杂，想再简化一下使用流程；
* 现有gpuimage在开关切换一个filter的时候开销较大，而且需要队列的移除移入操作；
* 现有gpuimage的ios和安卓各自实现不通用；

# gpuimagecpp

* 基于opengles3 
* 实现了几个XXXFilter特效
* 使用和扩展都更简洁方便

# 使用
```c++
//继承Filter类，实现各自的render()函数
class ShakeFilter: public Filter{s
    public:
        gic_uint render(gic_uint textureid);
};

//在任意地方new出来，调init()。
ShakeFilter* shake = new ShakeFilter();
OutSoulFilter* outsoul = new OutSoulFilter();
MultWindowFilter* mulwindwo = new MultWindowFilter();
FontFilter* font = new FontFilter();

shake->init("ShakeFilter", strdir.data());
outsoul->init("OutSoulFilter", strdir.data());
mulwindwo->init("MultWindowFilter", strdir.data());
        
//按照append顺序串行执行
append_filter(shake->get_id());
append_filter(outsoul->get_id());
append_filter(mulwindwo->get_id());


//运行时在任何地方动态开关任一filter.
shake->invisible();
outsoul->invisible();
mulwindwo->invisible();
shake->visible();
```


![image](https://github.com/xx8086/gpuimagecpp/blob/master/uml_gpuimagecpp_frame.jpg)
