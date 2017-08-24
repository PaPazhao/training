 
CLASS(fsm_name_t)		__fsm_name_t
fsm_name_t  				fsm_name_t

extern_simple_fsm(name, xxx)          
 
////////////////////////////// extern_simple_fsm 
typedef union fsm_name_t fsm_name_t;
                                  
union fsm_name_t {                             
                               
	uint_fast8_t fsm_name_t__chMask[(sizeof(struct{
         
		uint_fast8_t chState;                               
		xxxxx;

	}) + sizeof(uint_fast8_t) - 1) / sizeof(uint_fast8_t)];
};

////////////////////////////// simple_fsm 
simple_fsm(name, xxx)                                
typedef union fsm_name_t fsm_name_t;                             
 
typedef struct __fsm_name_t __fsm_name_t;     
struct __fsm_name_t {                         
  
	uint_fast8_t chState;                             
	xxxxx;                              
};  


////////////////////////////// extern_fsm_initialiser 
extern_fsm_initialiser(name, ...)                                  
                                 
typedef fsm_name_t *name_init_fn(fsm_name_t *ptFSM xxxx);  
extern  fsm_name_t *name_init(fsm_name_t *ptFSM xxxx);

 
////////////////////////////// fsm_initialiser 
fsm_initialiser(name, ...)
typedef fsm_name_t *name_init_fn(fsm_name_t *ptFSM xxxx);
fsm_name_t *name_init(fsm_name_t *ptFSM xxxx) 
{                                                                        
	CLASS(fsm_name_t) *ptThis = ( CLASS(fsm_name_t) *)ptFSM; 
	if (NULL == ptThis) {                                                
	return NULL;                                                     
	}                                                                    
	ptThis->chState = 0;

 	init_body(xxx_xxxx)                                                           
		xxx_xxxx                                                          
	return ptFSM;                                                        
}



////////////////////////////// extern_fsm_implementation 
extern_fsm_implementation(name, ...) 
typedef fsm_rt_t name_fn( fsm_name_t *ptFSM xxxx );     
extern fsm_rt_t name( fsm_name_t *ptFSM xxxx );






////////////////////////////// fsm_implementation 
fsm_implementation(name, ...)                                                                      
typedef fsm_rt_t name_fn( fsm_name_t *ptFSM xxx );              
fsm_rt_t name( fsm_name_t *ptFSM xxx )                            
{                                                                            
	CLASS(fsm_name_t) *ptThis = (CLASS(fsm_name_t) *)ptFSM;      
	if (NULL == ptThis) {                                                    
		return fsm_rt_err;                                                   
	}
	enum {                                                       
		START = 0,                                               
		ssss,
	};

 	body(...)                                                                
	switch (ptThis->chState) {                                               
		case 0:                                                              
		ptThis->chState++;   

		state(__STATE, ccc)                                                      
		case __STATE: {
			cccc;
		}
	                                                         
	}                                                                        
	 
	return fsm_rt_on_going;                                                  
}
 
////////////////////////////// init_fsm 
init_fsm(name, *fsm_name_t, ...)                             
name_init(*fsm_name_t __VA_ARGS__)


////////////////////////////// call_fsm 
call_fsm(name, __FSM, ...)                            
name(*fsm_name_t)