#pragma once
#include "Delegate.h"
#include "Container/ContainerTypes.h"

template<typename T>
class TMulticastDelegate;

/// @brief �����֐��L���X�g�p�f���Q�[�g�@���̂Ƃ���P�̃f���Q�[�g�𕡐��R���e�i�Ŏ����Ă��邾���B����֐���Remove������
/// @tparam ...Args ����
template<typename... Args>
class TMulticastDelegate<Args...>
{
public:
	using FunctorType = TDelegate<void(Args...)>;

	template<typename Class>
	using ClassFunction = FunctorType::ClassFunction<Class>;

	TMulticastDelegate() {};
	~TMulticastDelegate() { ClearFunction(); }

private:

	/// @brief �P�̃f���Q�[�g�̃R���e�i
	TVariableArray<FunctorType> m_invocationList;

public:

	/// @brief �����o�֐��R�Â�
	/// @tparam Class �C���X�^���X�̌^
	/// @param _instance �N���X�̃C���X�^���X
	/// @param _function ���s���郁���o�֐��̃|�C���^
	template<typename Class>
	void AddFunction(Class* _instance, ClassFunction<Class>&& _function)
	{
		m_invocationList.emplace_back();
		FunctorType& functor = m_invocationList.back();
		functor.BindFunction(_instance, _function);
	}

	/// @brief �ʏ�̊֐��i�ÓI�֐��A�����_�j�̕R�Â�
	/// @param _function �֐��|�C���^
	void AddFunction(FunctorType::StaticFunction _function)
	{
		m_invocationList.emplace_back();
		FunctorType& functor = m_invocationList.back();
		functor.BindFunction(_function);
	}

	/// @brief �S�֐����s
	/// @param ..._args ����
	void Broadcast(Args... _args)
	{
		for (auto&& functor : m_invocationList)
		{
			functor.Invoke(_args);
		}
	}

	void ClearFunction()
	{
		m_invocationList.clear();
	}
};