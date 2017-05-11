// functor.hpp

#ifndef FUNCTOR_HPP_INCLUDED
#define FUNCTOR_HPP_INCLUDED

template <typename T>
class IFunctor
{
public:
	virtual ~IFunctor() {}
	virtual void invoke(T t) = 0;
	virtual bool operator==(void*) = 0;
};

template <typename C, typename T>
class Functor : public IFunctor<T>
{
public:
	Functor(C* object, void(C::*method)(T t))
		: m_object(object)
		, m_method(method)
	{
	}

	void invoke(T t)
	{
		(*m_object.*m_method)(t);
	}

	bool operator==(void* object)
	{
		return m_object == object;
	}

private:
	C* m_object;
	void(C::*m_method)(T t);
};

#endif // FUNCTOR_HPP_INCLUDED
