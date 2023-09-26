#include "Class/ClassField.h"

/// @brief 同じクラスかどうか判定
/// @param  判定するクラス情報
/// @return 抽象クラスなので常にFalse
bool IClassField::IsA(const IClassField* _class) const
{
	return _class ? IsSameObjectTypePrivate(_class->GetObjectTypeInfo()) : false;
}

/// @brief このクラスが指定のクラスを継承しているかどうか
/// @param  指定のクラス
/// @return 抽象クラスなので常にFalse
bool IClassField::IsSubclassOf(const IClassField* _class) const
{
	const IClassField* classField = _class;

	// While回して継承元のクラスをたどる
	while (classField)
	{
		// 一致するやつがあったらTrue
		if (IsA(classField))
		{
			return true;
		}
		classField = classField->GetSuper();
	}

	return false;
}

/// @brief 親クラス取得
/// @return 親のクラス情報
const IClassField* IClassField::GetSuper() const
{
	return nullptr;
}

/// @brief オブジェクトのTypeInfo取得
/// @return オブジェクトのTypeInfo
const std::type_info* IClassField::GetObjectTypeInfo() const
{
	return nullptr;
}

/// @brief TypeInfoが同じものかどうか判定
/// @param _typeInfo 比較先のTypeInfo
/// @return 同じならTrue
bool IClassField::IsSameObjectTypePrivate(const std::type_info* _opponentTypeInfo) const
{
	// TypeInfoの一致比較
	if (const std::type_info* info = GetObjectTypeInfo())
	{
		return _opponentTypeInfo ? *info == *_opponentTypeInfo : false;
	}

	// Nullptr来てたらFalse
	return false;
}

/// @brief 一致オペレーター
/// @param _class 比較先クラス
/// @return IsAと同じ
bool IClassField::operator==(const IClassField* _class)
{
	return IsA(_class);
}
