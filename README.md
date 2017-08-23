# 定义一个状态机
## 语法:

```  
simple_fsm( <状态机名称>,
    def_params(
        参数列表                
    )
)
```  

## 实例:  
 
```  : 
/*! fsm used to output specified string */
simple_fsm( print_string,
    def_params(
        const char *pchStr;        //!< point to the target string
        uint16_t hwIndex;          //!< current index
        uint16_t hwLength;         //!< claimed length of the target string, it is used to prevent buffer overflow 
    )
)
```  

## 状态机的引用：  
	
状态机实际上就是一个掩码结构体，通过 `fsm()` 对这个状态机进行引用

- 语法：  
  
	```  
	fsm(<状态机名称>)
	```  
	
- 实例:  
	
	```  
	//! 定义了一个本地的状态机控制块
	static fsm( print_string ) s_fsmPrintString;     
	```  


# extern 一个状态机

## 语法:

```  
extern_simple_fsm( <状态机名称>,
    def_params(
        参数列表                
    )
)

```  

## 实例:  

```  : 
/*! fsm used to output specified string */
extern_simple_fsm( print_string,
    def_params(
        const char *pchStr;        //!< point to the target string
        uint16_t hwIndex;          //!< current index
        uint16_t hwLength;         //!< claimed length of the target string, it is used to prevent buffer overflow 
    )
)
```  


# 状态机初始化函数
## 语法:
```  
fsm_initialiser( <状态机名称>,
    args(           
        <状态机初始化函数的形参列表，参数用逗号隔开，如果真的没有形参，可以省略该部分，讲真，没有形参，你要initialiser作甚？>
    ))

    init_body (
        <初始化函数的函数体，用普通C语言语法即可>
        /* 如果初始化过程中发生了任何错误需要放弃初始化并立即退出，使用 abort_init() */
    )
```  




## 实例:  
 
``` 
fsm_initialiser( print_string,
    args(           
        const char *pchString, uint16_t hwSize
    ))
    
    init_body (
        if (NULL == pchString || 0 == hwSize) {
            abort_init();                                       //!< illegal parameter
        } else if (strlen(pchString) < hwSize) {
            abort_init();                                       //!< buffer overflow
        }

        this.pchStr = pchString;  
        this.hwLength = hwSize;
    )
```

>注意  
> `//!< <状态机名称>_init  就是初始化函数的函数名。`  
> `print_string_init_fn *fnInit = &print_string_init;`   

# extern 状态机初始化函数
语法：

```
extern_simple_fsm_initialiser( <状态机名称>,
    args(           
        <状态机初始化函数的形参列表，参数用逗号隔开，如果真的没有形参，可以省略该部分，讲真，没有形参，你要initialiser作甚？>
    
    )
)

```

例子：

```
/*! fsm used to output specified string */
extern_simple_fsm_initialiser( print_string,
    args(           
        const char *pchString, uint16_t hwSize
    )
)

```

# 如何初始化一个状态机
语法：

```

init_fsm(   <状态机名称>, <目标状态机控制块的地址>, 
    args( 
        <状态机初始化函数的实参列表，参数用逗号隔开，如果没有实参，可以省略该部分> 
     ));

该函数的返回值是地址：
     NULL          初始化过程中出错
     NOT NULL   <目标状态机控制块的地址>
```

例子:

```

//! 定义了一个状态机控制块
static fsm(print_string)  s_fsmPrintString;

#define DEMO_STRING   "Hello FSM World!\r\n"

    if (NULL == init_fsm(    print_string, & s_fsmPrintString,
        args( 
            DEMO_STRING,                      //!< target string    
            sizeof(DEMO_STRING) - 1))) {      //!< String Length
         /* failed to initialize the FSM, put error handling code here */
     }
```

# 如何实现状态机

语法:

```
fsm_implementation(  <状态机名称>, 
        args( <状态机的形参列表，参数用逗号隔开，如果没有形参，可以省略这部分> )
    )
    def_states( <列举所有状态机状态，用逗号隔开，确保状态机的入口状态列在第一的位置> )               

    <局部变量列表>

    body (
         on_start(  
             <状态机复位后第一次运行时，运行且只运行一次的代码，通常放一些状态机内部的初始化代码，如果无所事事，可以省略这个部分>
         )  
      
        <状态机所有的状态实现>
    )
```

例子:

```
fsm_implementation(  print_string )
    def_states( CHECK_LENGTH, OUTPUT_CHAR )               

    body (
         on_start(  
             this.hwIndex = 0;         //!< reset index
         )  
      
        ...
    )

```

当你使用 fsm_implementation 的时候，我们的宏木板还会自动定义一个函数原型，这样，你就可以
    用这个函数圆形去定义指向 当前初始化函数 的函数指针。函数原型的名称如下：

  ` <状态机名称>_fn`
这里，系统顺便定义了一个函数原型，`print_string_fn`，你可以用`print_string_fn` 直接定义函数指针：

```
print_string_fn *fnFSM = &print_string;   //!< <状态机名称> 就是状态机函数的名称。
```


# extern 一个状态机函数

语法:

```
extern_fsm_implementation(  <状态机名称>, 
        args( <状态机的形参列表，参数用逗号隔开，如果没有形参，可以省略这部分> )
    )

```

实例:

```

#include "ooc.h"
#include "simple_fsm.h"

...

extern_fsm_implementation(  print_string );

...

这里，系统顺便定义了一个函数原型，print_string_fn，你可以用print_string_fn 直接定义函数指针：
    print_string_fn *fnFSM = &print_string;   //!< <状态机名称> 就是状态机函数的名称。

```


# 实现一个状态
## 语法:
```
state( <状态名称>,
 
    <状态实现代码，C语言实现>

    fsm_on_going();
)
```

## 切换状态：
在实现状态的过程中，状态的切换要通过 transfer_to() 来实现，它将立即终止当前状态代码的执行，
并跳转到目标状态中，其语法如下：
 
```    
transfer_to( <目标状态的名称> )
```
实际上 transfer_to() 等效于以下的组合

```
update_state_to( <目标状态> )
fsm_on_going();
```

状态实现的时候，如果需要更新状态机的返回值，则可以使用下列方式：

```
fsm_on_going()                立即终止当前状态，并让状态机返回fsm_rt_on_going;
fsm_cpl()                     立即终止当前状态，复位状态机，并让状态机返回fsm_rt_cpl;
fsm_reset()                   仅复位状态机，不影响状态机返回值（通常配合fsm_on_going()和fsm_report() 使用
fsm_report( <任意负数> )       立即终止当前状态，并返回错误码（任意小于等于fsm_rt_err）的值
```

##例子:

```

fsm_implementation(  print_string )
    def_states( CHECK_LENGTH, OUTPUT_CHAR )               

    body (
         on_start(  
             this.hwIndex = 0;         //!< reset index
         )  
      
        state ( CHECK_LENGTH,
            if ( this.hwIndex >= this.hwLength ) {
                 fsm_cpl();               
            }
            update_state_to ( OUTPUT_CHAR );              //! deliberately ignore the following fsm_on_going() in order to fall through to next state
            // fsm_on_going();        
        )

        state ( OUTPUT_CHAR,
             if (SERIAL_OUT( this.pchStr[ this.hwIndex ] )) {
                   this.hwIndex++;
                   transfer_to ( CHECK_LENGTH );
             }

             fsm_on_going();
        )
    )

```
# 如何调用状态机

## 语法:

```
call_fsm ( <状态机名称>, <状态机控制块的地址>
    args( <状态机的实参列表，参数用逗号隔开。如果没有实参，可以省略该部分> )
)

```

该函数的返回值是状态机的运行状态 `fsm_rt_t`：  

``` 
fsm_rt_err                	状态机出现了意料之外的，且自身无法处理的错误，例如无效的参数  
fsm_rt_on_going       	    状态机正在执行  
fsm_rt_cpl                	状态机已经完成
```

## 实例：

```
static fsm(print_string) s_fsmPrintSting;

void main(void)
{
     ...
     while(1) {
         ...
         if (fsm_rt_cpl == call_fsm( print_string, &s_fsmPrintString )) {
              /* fsm is complete, do something here */
         }
     }
}
```
