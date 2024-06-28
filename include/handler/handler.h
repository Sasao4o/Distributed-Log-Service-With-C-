#include<string>
#ifndef HandlerModule
#define HandlerModule

class Handler { 
   public:
   virtual void Join(std::string& name, std::string& address) = 0;
   virtual void Leave(std::string& name) = 0;
};

#endif