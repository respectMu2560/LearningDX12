#pragma once
#include <functional>

// 部分特殊化用テンプレート
template<typename T>
class TDelegate;

/// @brief シングルキャスト用デリゲート（今のところstd::functionのラッパー）
/// @tparam Ret 関数の返り値
/// @tparam ...Args 関数の引数
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

	/// @brief メンバ関数紐づけ
	/// @tparam Class 紐づけするクラス型
	/// @param _instance クラスのインスタンス
	/// @param _function クラスのメンバ関数
	template<typename Class>
	void BindFunction(Class* _instance, ClassFunction<Class> _function)
	{
		// TODO：ラムダ式のキャプチャは生存期間が見れないので他の形がいい
		m_function = [_intstance, _funciton](Args... _args) -> ReturnType
		{
			return (_instance->*_function)(_args...);
		};
	}

	/// @brief ラムダ式、Static関数、普通の関数紐づけ
	/// @param _function 関数ポインタ
	void BindFunction(StaticFunction _function)
	{
		m_function = _function;
	}

	/// @brief 関数実行
	/// @param ..._args 宣言時に指定された引数
	/// @return 宣言時に指定された返り値
	ReturnType Invoke(Args... _args)
	{
		return std::invoke(m_function(_args...));
	}

	/// @brief 関数実行オペレーター
	/// @param ..._args 宣言時に指定された引数
	/// @return 宣言時に指定された返り値
	ReturnType operator ()(Args... _args)
	{
		return Invoke(_args...);
	}

	/// @brief 関数紐づけ解除
	void UnBind()
	{
		m_function = nullptr;
	}

private:
	FunctionType m_function;
};