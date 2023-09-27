#pragma once
#include <functional>

// �������ꉻ�p�e���v���[�g
template<typename T>
class TDelegate;

/// @brief �V���O���L���X�g�p�f���Q�[�g�i���̂Ƃ���std::function�̃��b�p�[�j
/// @tparam Ret �֐��̕Ԃ�l
/// @tparam ...Args �֐��̈���
template<typename ReturnType,typename... Args>
class TDelegate<ReturnType(Args...)>
{
public:

	using FunctionType = std::function<ReturnType(Args...)>;

	using StaticFunction = ReturnType(*)(Args...);

	template<typename Class>
	using ClassFunction = ReturnType(Class::*)(Args...);

public:

	TDelegate() {};
	~TDelegate() { UnBind(); }

	TDelegate(TDelegate&& _delegate)
	{
		m_function = _delegate.m_function;
	}

	/// @brief �����o�֐��R�Â�
	/// @tparam Class �R�Â�����N���X�^
	/// @param _instance �N���X�̃C���X�^���X
	/// @param _function �N���X�̃����o�֐�
	template<typename Class>
	void BindFunction(Class* _instance, ClassFunction<Class> _function)
	{
		// TODO�F�����_���̃L���v�`���͐������Ԃ�����Ȃ��̂ő��̌`������
		m_function = [_intstance, _funciton](Args... _args) -> ReturnType
		{
			return (_instance->*_function)(_args...);
		};
	}

	/// @brief �����_���AStatic�֐��A���ʂ̊֐��R�Â�
	/// @param _function �֐��|�C���^
	void BindFunction(StaticFunction _function)
	{
		m_function = _function;
	}

	/// @brief �֐����s
	/// @param ..._args �錾���Ɏw�肳�ꂽ����
	/// @return �錾���Ɏw�肳�ꂽ�Ԃ�l
	ReturnType Invoke(Args... _args)
	{
		return std::invoke(m_function(_args...));
	}

	/// @brief �֐����s�I�y���[�^�[
	/// @param ..._args �錾���Ɏw�肳�ꂽ����
	/// @return �錾���Ɏw�肳�ꂽ�Ԃ�l
	ReturnType operator ()(Args... _args)
	{
		return Invoke(_args...);
	}

	/// @brief �֐��R�Â�����
	void UnBind()
	{
		m_function = nullptr;
	}

private:
	FunctionType m_function;
};