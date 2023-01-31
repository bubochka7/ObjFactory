#pragma once
#include <memory>
#if __has_cpp_attribute [[nodiscard]]
#define NODISCARD
#endif
template<class T>
NODISCARD struct newPolicy
{
	template<typename ...Args>
	static auto make(Args&&...args) ->decltype(new T(std::forward<Args>(args)...))	
	{
		return new T(std::forward<Args>(args)...);
	}
};
template<class T>
struct uniquePtrPolicy
{
	template<typename ...Args>
	static auto make(Args&&...args) ->decltype(std::make_unique<T, Args...>(std::forward<Args>(args)...))
	{
		return std::make_unique<T, Args...>(std::forward<Args>(args)...);
	}
};
template<class T,template<class>  class Policy>
class ObjFactory 
{
public:
	template<typename ...Args>
	static auto create(Args&&...args) ->decltype(Policy<T>::make(std::forward<Args>(args)...))
	{
		return Policy<T>::make(std::forward<Args>(args)...);
	}	
};
template<class T>
using newOpFactory = ObjFactory<T, newPolicy>;
template<class T>
using uptrFactory  = ObjFactory<T, uniquePtrPolicy>;
#include "FactotyCreateFunctions.inl"