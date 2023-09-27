#pragma once
#include "Delegate.h"
#include "Container/ContainerTypes.h"

template<typename T>
class TMulticastDelegate;

/// @brief 複数関数キャスト用デリゲート　今のところ単体デリゲートを複数コンテナで持っているだけ。特定関数のRemove未実装
/// @tparam ...Args 引数
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

	/// @brief 単体デリゲートのコンテナ
	TVariableArray<FunctorType> m_invocationList;

public:

	/// @brief メンバ関数紐づけ
	/// @tparam Class インスタンスの型
	/// @param _instance クラスのインスタンス
	/// @param _function 実行するメンバ関数のポインタ
	template<typename Class>
	void AddFunction(Class* _instance, ClassFunction<Class>&& _function)
	{
		m_invocationList.emplace_back();
		FunctorType& functor = m_invocationList.back();
		functor.BindFunction(_instance, _function);
	}

	/// @brief 通常の関数（静的関数、ラムダ）の紐づけ
	/// @param _function 関数ポインタ
	void AddFunction(FunctorType::StaticFunction _function)
	{
		m_invocationList.emplace_back();
		FunctorType& functor = m_invocationList.back();
		functor.BindFunction(_function);
	}

	/// @brief 全関数実行
	/// @param ..._args 引数
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