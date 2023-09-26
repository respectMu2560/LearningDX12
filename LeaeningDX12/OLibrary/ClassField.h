#pragma once

// typeInfo
#include <typeinfo>

/// @brief オブジェクトのクラス情報纏めた抽象クラス
class IClassField
{
public:

	/// @brief 同じクラスかどうか判定
	/// @param  判定するクラス情報
	/// @return 抽象クラスなので常にFalse
	bool IsA(const IClassField* _class) const;

	/// @brief このクラスが指定のクラスを継承しているかどうか
	/// @param  指定のクラス
	/// @return 抽象クラスなので常にFalse
	bool IsSubclassOf(const IClassField* _class) const;

	/// @brief 親クラス取得
	/// @return 親のクラス情報
	virtual const IClassField* GetSuper() const;

protected:
	/// @brief オブジェクトのTypeInfo取得
	/// @return オブジェクトのTypeInfo
	virtual const std::type_info* GetObjectTypeInfo() const;

	/// @brief TypeInfoが同じものかどうか判定
	/// @param _typeInfo 比較先のTypeInfo
	/// @return 同じならTrue
	bool IsSameObjectTypePrivate(const std::type_info* _opponentTypeInfo) const;

public:
	// operators

	/// @brief 一致オペレーター
	/// @param _class 比較先クラス
	/// @return IsAと同じ
	bool operator ==(const IClassField* _class);
};

/// @brief オブジェクト毎のテンプレートクラス情報パラメーター
/// @tparam Type オブジェクトのクラス
/// @tparam Super オブジェクトの継承元クラス
template<typename Type, typename Super>
class TClassField : public IClassField
{
public:
	/// @brief Superクラス取得
	/// @return オブジェクトの継承元クラスのClassField
	const IClassField* GetSuper() const override
	{
		return Super::StaticClass();
	}

private:
	/// @brief オブジェクトのTypeInfo取得
	/// @return オブジェクトのTypeInfo
	const std::type_info* GetObjectTypeInfo() const override
	{
		static constexpr std::type_info&& TYPE_INFO = typeid(Type);
		return TYPE_INFO;
	}
};