#ifndef DEPENDANT_VAR_H
#define DEPENDANT_VAR_H

#include <functional>

template<typename T, typename... Rest>
class dependant_var_checker : dependant_var_checker<Rest...>
{
private:
	const T& tref;
	T t;
private:
	dependant_var_checker(const T& _tref, const Rest&... rest):
		dependant_var_checker<Rest...>(rest...),
		tref(_tref)
	{
	}

	bool check() const
	{
		if (tref != t)
			return false;
		return dependant_var_checker<Rest...>::check();
	}

	void set()
	{
		t = tref;
		dependant_var_checker<Rest...>::set();
	}

	template<class>
	friend class dependant_var;
};

template<typename T>
class dependant_var_checker<T>
{
private:
	const T& tref;
	T t;
private:
	dependant_var_checker(const T& _tref):
		tref(_tref)
	{
	}

	bool check() const
	{
		return tref == t;
	}

	void set()
	{
		t = tref;
	}

	template<class>
	friend class dependant_var;

	template<class, class...>
	friend class dependant_var_checker;
};

template<class>
class dependant_var;

template<typename R, typename... Targs>
class dependant_var<R(Targs...)>
{
private:
	bool first = true;
	dependant_var_checker<Targs...> checker;
	R r;
	std::function<R()> f;
public:
	template<typename F>
	dependant_var(F _f, const Targs&... args):
		checker(args...),
		f(std::bind(_f, std::ref(args)...))
	{
	}

	operator R()
	{
		if (first == false && checker.check())
			return r;
		first = false;
		checker.set();
		r = f();
		return r;
	}
};

#endif
